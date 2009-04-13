#include "abstracttextbuffer.h"
#include "textchunk.h"
#include "user.h"

#include <libinftext/inf-text-buffer.h>

#include <glib-object.h>

static GObjectClass *parent_class;

static void qinf_text_abstract_buffer_init( GTypeInstance *instance,
    gpointer g_class )
{
}

static void qinf_text_abstract_buffer_finalize( GObject *object )
{
    G_OBJECT_CLASS(parent_class)->finalize(object);
}

static void qinf_text_abstract_buffer_class_init( gpointer g_class,
    gpointer class_data )
{
    GObjectClass* object_class;
    object_class = G_OBJECT_CLASS(g_class);

    parent_class = G_OBJECT_CLASS(g_type_class_peek_parent(g_class));

    object_class->finalize = qinf_text_abstract_buffer_finalize;
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
        0
    );

    return QINF_TEXT_ABSTRACT_BUFFER(object);
}

namespace QInfinity
{

void AbstractTextBuffer::bufferIfaceInit( gpointer g_iface,
    gpointer iface_data )
{
}

void AbstractTextBuffer::textBufferIfaceInit( gpointer g_iface,
    gpointer iface_data )
{
    InfTextBufferIface *iface;
    iface = (InfTextBufferIface*)g_iface;

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
    absBuffer->wrapper->onInsertText( offset,
        TextChunk( chunk, false ),
        User::wrap( user ) );
}

void AbstractTextBuffer::erase_text_cb( InfTextBuffer *buffer,
    unsigned int offset,
    unsigned int length,
    InfUser *user )
{
    QInfTextAbstractBuffer *absBuffer = QINF_TEXT_ABSTRACT_BUFFER(buffer);
    absBuffer->wrapper->onEraseText( offset,
        length,
        User::wrap( user ) );
}

}

