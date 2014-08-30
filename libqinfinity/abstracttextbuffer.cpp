/*
 * Copyright 2009  Gregory Haynes <greg@greghaynes.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "abstracttextbuffer.h"
#include "textchunk.h"
#include "user.h"

#include <libinftext/inf-text-buffer.h>
#include <libinftext/inf-text-chunk.h>

#include <glib-object.h>

typedef struct _InfTextBufferIter InfTextBufferIter;
struct _InfTextBufferIter
{
    InfTextChunkIter chunk_iter;
};

typedef struct _QInfTextAbstractBufferPrivate QInfTextAbstractBufferPrivate;
struct _QInfTextAbstractBufferPrivate
{
    QInfinity::AbstractTextBuffer *wrapper;
    gchar *encoding;
    gboolean modified;
    InfTextChunk *chunk;
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
    priv->chunk = 0;
}

static void qinf_text_abstract_buffer_finalize( GObject *object )
{
    QInfTextAbstractBuffer *abs_buffer;
    QInfTextAbstractBufferPrivate *priv;

    abs_buffer = QINF_TEXT_ABSTRACT_BUFFER(object);
    priv = QINF_TEXT_ABSTRACT_BUFFER_PRIVATE(abs_buffer);

    g_free(priv->encoding);
    inf_text_chunk_free(priv->chunk);

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
            g_assert(priv->encoding == NULL);
            g_assert(priv->chunk == NULL);

            priv->encoding = g_value_dup_string(value);
            priv->chunk = inf_text_chunk_new(priv->encoding);
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

static unsigned int qinf_text_abstract_buffer_get_length( InfTextBuffer *buffer )
{
    QInfTextAbstractBufferPrivate* priv;
    priv = QINF_TEXT_ABSTRACT_BUFFER_PRIVATE(buffer);
    return inf_text_chunk_get_length(priv->chunk);
}

static InfTextChunk* qinf_text_abstract_buffer_get_slice(InfTextBuffer* buffer,
    guint pos,
    guint len)
{
    QInfTextAbstractBufferPrivate* priv;
    priv = QINF_TEXT_ABSTRACT_BUFFER_PRIVATE(buffer);
    return inf_text_chunk_substring(priv->chunk, pos, len);
}

static void qinf_text_abstract_buffer_destroy_iter(InfTextBuffer* buffer,
    InfTextBufferIter* iter)
{
    g_slice_free(InfTextBufferIter, iter);
}

static gboolean qinf_text_abstract_buffer_iter_next(InfTextBuffer* buffer,
    InfTextBufferIter* iter)
{
    return inf_text_chunk_iter_next(&iter->chunk_iter);
}

static gboolean qinf_text_abstract_buffer_iter_prev(InfTextBuffer* buffer,
    InfTextBufferIter* iter)
{
    return inf_text_chunk_iter_prev(&iter->chunk_iter);
}

static gpointer qinf_text_abstract_buffer_iter_get_text(InfTextBuffer* buffer,
    InfTextBufferIter* iter)
{
    return g_memdup(
        inf_text_chunk_iter_get_text(&iter->chunk_iter),
        inf_text_chunk_iter_get_bytes(&iter->chunk_iter)
    );
}

static guint qinf_text_abstract_buffer_iter_get_length(InfTextBuffer* buffer,
    InfTextBufferIter* iter)
{
    return inf_text_chunk_iter_get_length(&iter->chunk_iter);
}

static gsize qinf_text_abstract_buffer_iter_get_bytes(InfTextBuffer* buffer,
    InfTextBufferIter* iter)
{
    return inf_text_chunk_iter_get_bytes(&iter->chunk_iter);
}

static guint qinf_text_abstract_buffer_iter_get_author(InfTextBuffer* buffer,
                                               InfTextBufferIter* iter)
{
    return inf_text_chunk_iter_get_author(&iter->chunk_iter);
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
    static GType abstract_buffer_type = 0;

    if(!abstract_buffer_type)
    {
        static const GTypeInfo abstract_buffer_type_info = {
            sizeof(struct _QInfTextAbstractBufferClass),  /* class_size */
            NULL,                               /* base_init */
            NULL,                               /* base_finalize */
            qinf_text_abstract_buffer_class_init, /* class_init */
            NULL,                               /* class_finalize */
            NULL,                               /* class_data */
            sizeof(struct _QInfTextAbstractBuffer),       /* instance_size */
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

        abstract_buffer_type = g_type_register_static(
            G_TYPE_OBJECT,
            "QInfTextAbstractBuffer",
            &abstract_buffer_type_info,
            (GTypeFlags)0
        );

        g_type_add_interface_static(
            abstract_buffer_type,
            INF_TYPE_BUFFER,
            &buffer_info
        );

        g_type_add_interface_static(
            abstract_buffer_type,
            INF_TEXT_TYPE_BUFFER,
            &text_buffer_info
        );
    }

    return abstract_buffer_type;
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
    iface->get_length = qinf_text_abstract_buffer_get_length;
    iface->get_slice = qinf_text_abstract_buffer_get_slice;
    iface->destroy_iter = qinf_text_abstract_buffer_destroy_iter;
    iface->iter_next = qinf_text_abstract_buffer_iter_next;
    iface->iter_prev = qinf_text_abstract_buffer_iter_prev;
    iface->iter_get_text = qinf_text_abstract_buffer_iter_get_text;
    iface->iter_get_length = qinf_text_abstract_buffer_iter_get_length;
    iface->iter_get_bytes = qinf_text_abstract_buffer_iter_get_bytes;
    iface->iter_get_author = qinf_text_abstract_buffer_iter_get_author;
    iface->insert_text = AbstractTextBuffer::insert_text_cb;
    iface->erase_text = AbstractTextBuffer::erase_text_cb;
}

AbstractTextBuffer::AbstractTextBuffer( const QString &encoding,
    QObject *parent )
    : TextBuffer( INF_TEXT_BUFFER(qinf_text_abstract_buffer_new( encoding.toAscii(), this )),
        parent )
{
    QInfTextAbstractBuffer *absBuffer = QINF_TEXT_ABSTRACT_BUFFER(gobject());
    QInfTextAbstractBufferPrivate *priv;

    priv = QINF_TEXT_ABSTRACT_BUFFER_PRIVATE(absBuffer);
    priv->wrapper = this;
}

AbstractTextBuffer::~AbstractTextBuffer()
{
}

InfTextChunk *AbstractTextBuffer::chunk()
{
    QInfTextAbstractBuffer *abs_buffer;
    QInfTextAbstractBufferPrivate *priv;

    abs_buffer = QINF_TEXT_ABSTRACT_BUFFER(gobject());
    priv = QINF_TEXT_ABSTRACT_BUFFER_PRIVATE(abs_buffer);
    return priv->chunk;
}

void AbstractTextBuffer::insert_text_cb( InfTextBuffer *buffer,
    unsigned int offset,
    InfTextChunk *chunk,
    InfUser *user )
{
    QInfTextAbstractBuffer *absBuffer = QINF_TEXT_ABSTRACT_BUFFER(buffer);
    QInfTextAbstractBufferPrivate *priv;

    priv = QINF_TEXT_ABSTRACT_BUFFER_PRIVATE(absBuffer);

    inf_text_chunk_insert_chunk(priv->chunk, offset, chunk);

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

    inf_text_chunk_erase(priv->chunk, offset, length);

    priv->wrapper->onEraseText( offset,
        length,
        User::wrap( user ) );
}

}

