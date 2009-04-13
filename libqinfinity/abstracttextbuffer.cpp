#include "abstracttextbuffer.h"
#include "textchunk.h"
#include "user.h"

#include <libinftext/inf-text-buffer.h>

#include <glib-object.h>

typedef struct _QInfTextAbstractBufferPrivate QInfTextAbstractBufferPrivate;
struct _QInfTextAbstractBufferPrivate
{
    QInfinity::AbstractTextBuffer *wrapper;
    gchar *encoding;
    gboolean modified;
};

enum {
    PROP_0,

    PROP_MODIFIED,

    PROP_ENCODING
};

#define QINF_TEXT_ABSTRACT_BUFFER_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj), QINF_TEXT_TYPE_ABSTRACT_BUFFER, QInfTextAbstractBufferPrivate))

static GObjectClass *parent_class;

GType qinf_text_abstract_buffer_get_type();

static void qinf_text_abstract_buffer_init( GTypeInstance *instance,
    gpointer g_class )
{
    QInfTextAbstractBuffer *abs_buffer;
    QInfTextAbstractBufferPrivate *priv;

    abs_buffer = QINF_TEXT_ABSTRACT_BUFFER(instance);
    priv = QINF_TEXT_ABSTRACT_BUFFER_PRIVATE(abs_buffer);
    
    priv->encoding = 0;
    priv->modified = FALSE;
}

static void qinf_text_abstract_buffer_finalize( GObject *object )
{
    QInfTextAbstractBuffer *abs_buffer;
    QInfTextAbstractBufferPrivate *priv;

    abs_buffer = QINF_TEXT_ABSTRACT_BUFFER(object);
    priv = QINF_TEXT_ABSTRACT_BUFFER_PRIVATE(abs_buffer);

    g_free(priv->encoding);

    G_OBJECT_CLASS(parent_class)->finalize(object);
}

static void qinf_text_abstract_buffer_set_property( GObject *object,
    guint prop_id,
    const GValue *value,
    GParamSpec *pspec )
{
    QInfTextAbstractBuffer *abs_buffer;
    QInfTextAbstractBufferPrivate *priv;

    abs_buffer = QINF_TEXT_ABSTRACT_BUFFER(object);
    priv = QINF_TEXT_ABSTRACT_BUFFER_PRIVATE(abs_buffer);

    switch(prop_id)
    {
        case PROP_ENCODING:
            priv->encoding = g_value_dup_string(value);
            break;
        case PROP_MODIFIED:
            priv->modified = g_value_get_boolean(value);
    }
}

static void qinf_text_abstract_buffer_get_property( GObject *object,
    guint prop_id,
    GValue *value,
    GParamSpec *pspec )
{
    QInfTextAbstractBuffer *abs_buffer;
    QInfTextAbstractBufferPrivate *priv;

    abs_buffer = QINF_TEXT_ABSTRACT_BUFFER(object);
    priv = QINF_TEXT_ABSTRACT_BUFFER_PRIVATE(abs_buffer);

    switch(prop_id)
    {
        case PROP_ENCODING:
            g_value_set_string(value, priv->encoding);
            break;
        case PROP_MODIFIED:
            g_value_set_boolean(value, priv->modified);
    }
}

static void qinf_text_abstract_buffer_set_modified( InfBuffer *buffer,
    gboolean modified )
{
    QInfTextAbstractBuffer *abs_buffer;
    QInfTextAbstractBufferPrivate *priv;

    abs_buffer = QINF_TEXT_ABSTRACT_BUFFER(buffer);
    priv = QINF_TEXT_ABSTRACT_BUFFER_PRIVATE(abs_buffer);

    if(priv->modified != modified)
    {
        priv->modified = modified;
        g_object_notify(G_OBJECT(buffer), "modified");
    }
}

static gboolean qinf_text_abstract_buffer_get_modified( InfBuffer *buffer )
{
    return QINF_TEXT_ABSTRACT_BUFFER_PRIVATE(buffer)->modified;
}

static const gchar *qinf_text_abstract_buffer_get_encoding( InfTextBuffer *buffer )
{
    return QINF_TEXT_ABSTRACT_BUFFER_PRIVATE(buffer)->encoding;
}

static void qinf_text_abstract_buffer_class_init( gpointer g_class,
    gpointer class_data )
{
    GObjectClass* object_class;
    object_class = G_OBJECT_CLASS(g_class);

    parent_class = G_OBJECT_CLASS(g_type_class_peek_parent(g_class));
    g_type_class_add_private(g_class, sizeof(QInfTextAbstractBufferPrivate));

    object_class->finalize = qinf_text_abstract_buffer_finalize;
    object_class->set_property = qinf_text_abstract_buffer_set_property;
    object_class->get_property = qinf_text_abstract_buffer_get_property;

    g_object_class_override_property(object_class, PROP_MODIFIED, "modified");

    g_object_class_install_property(
        object_class,
        PROP_ENCODING,
        g_param_spec_string(
            "encoding",
            "Encoding",
            "The character encoding of the text buffer.",
            0,
            (GParamFlags)(G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY)
        )
    );
}

GType qinf_text_abstract_buffer_get_type()
{
    static GType default_buffer_type = 0;

    if(!default_buffer_type)
    {
        static const GTypeInfo default_buffer_type_info = {
            sizeof(QInfTextAbstractBufferClass),  /* class_size */
            NULL,                               /* base_init */
            NULL,                               /* base_finalize */
            qinf_text_abstract_buffer_class_init, /* class_init */
            NULL,                               /* class_finalize */
            NULL,                               /* class_data */
            sizeof(QInfTextAbstractBuffer),       /* instance_size */
            0,                                  /* n_preallocs */
            qinf_text_abstract_buffer_init,       /* instance_init */
            NULL                                /* value_table */
        };

        static const GInterfaceInfo buffer_info = {
            QInfinity::AbstractTextBuffer::bufferIfaceInit,
            NULL,
            NULL
        };

        static const GInterfaceInfo text_buffer_info = {
            QInfinity::AbstractTextBuffer::textBufferIfaceInit,
            NULL,
            NULL
        };

        default_buffer_type = g_type_register_static(
            G_TYPE_OBJECT,
            "QInfTextAbstractBuffer",
            &default_buffer_type_info,
            (GTypeFlags)0
        );

        g_type_add_interface_static(
            default_buffer_type,
            INF_TYPE_BUFFER,
            &buffer_info
        );

        g_type_add_interface_static(
            default_buffer_type,
            INF_TEXT_TYPE_BUFFER,
            &text_buffer_info
        );
    }

    return default_buffer_type;
}

QInfTextAbstractBuffer *qinf_text_abstract_buffer_new( const char *encoding,
    QInfinity::AbstractTextBuffer *wrapper )
{
    void *object;

    object = g_object_new(
        QINF_TEXT_TYPE_ABSTRACT_BUFFER,
        "encoding", encoding,
        0
    );

    return QINF_TEXT_ABSTRACT_BUFFER(object);
}

namespace QInfinity
{

void AbstractTextBuffer::bufferIfaceInit( gpointer g_iface,
    gpointer iface_data )
{
    InfBufferIface *iface;
    iface = (InfBufferIface*)g_iface;

    iface->set_modified = qinf_text_abstract_buffer_set_modified;
    iface->get_modified = qinf_text_abstract_buffer_get_modified;
}

void AbstractTextBuffer::textBufferIfaceInit( gpointer g_iface,
    gpointer iface_data )
{
    InfTextBufferIface *iface;
    iface = (InfTextBufferIface*)g_iface;

    iface->get_encoding = qinf_text_abstract_buffer_get_encoding;
    iface->insert_text = AbstractTextBuffer::insert_text_cb;
    iface->erase_text = AbstractTextBuffer::erase_text_cb;
}

AbstractTextBuffer::AbstractTextBuffer( const QString &encoding,
    QObject *parent )
    : TextBuffer( INF_TEXT_BUFFER(qinf_text_abstract_buffer_new( encoding.toAscii(), this )),
        parent )
{
}

AbstractTextBuffer::~AbstractTextBuffer()
{
}


void AbstractTextBuffer::insert_text_cb( InfTextBuffer *buffer,
    unsigned int offset,
    InfTextChunk *chunk,
    InfUser *user )
{
    QInfTextAbstractBuffer *absBuffer = QINF_TEXT_ABSTRACT_BUFFER(buffer);
    QInfTextAbstractBufferPrivate *priv;

    priv = QINF_TEXT_ABSTRACT_BUFFER_PRIVATE(absBuffer);
    priv->wrapper->onInsertText( offset,
        TextChunk( chunk, false ),
        User::wrap( user ) );
}

void AbstractTextBuffer::erase_text_cb( InfTextBuffer *buffer,
    unsigned int offset,
    unsigned int length,
    InfUser *user )
{
    QInfTextAbstractBuffer *absBuffer = QINF_TEXT_ABSTRACT_BUFFER(buffer);
    QInfTextAbstractBufferPrivate *priv;

    priv = QINF_TEXT_ABSTRACT_BUFFER_PRIVATE(absBuffer);
    priv->wrapper->onEraseText( offset,
        length,
        User::wrap( user ) );
}

}

