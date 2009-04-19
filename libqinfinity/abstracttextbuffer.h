#ifndef QINFINITY_ABSTRACT_TEXT_BUFFER_H
#define QINFINITY_ABSTRACT_TEXT_BUFFER_H

#include "textbuffer.h"

#include <glib-object.h>

class QString;

namespace QInfinity
{

class TextChunk;

class AbstractTextBuffer
    : public TextBuffer
{
    public:
        static void bufferIfaceInit( gpointer g_iface,
            gpointer iface_data );
        static void textBufferIfaceInit( gpointer g_iface,
            gpointer iface_data );

        /**
         * @brief Create a text buffer base class.
         */
        AbstractTextBuffer( const QString &encoding,
            QObject *parent = 0 );
        virtual ~AbstractTextBuffer();

    protected:
        virtual void onInsertText( unsigned int offset,
            const TextChunk &chunk,
            User *user ) = 0;
        virtual void onEraseText( unsigned int offset,
            unsigned int length,
            User *user ) = 0;

    private:
        static void insert_text_cb( InfTextBuffer *buffer,
            unsigned int offset,
            InfTextChunk *chunk,
            InfUser *user );
        static void erase_text_cb( InfTextBuffer *buffer,
            unsigned int offset,
            unsigned int length,
            InfUser *user );

};

}

G_BEGIN_DECLS

#define QINF_TEXT_TYPE_ABSTRACT_BUFFER                 (qinf_text_abstract_buffer_get_type())
#define QINF_TEXT_ABSTRACT_BUFFER(obj)                 (G_TYPE_CHECK_INSTANCE_CAST((obj), QINF_TEXT_TYPE_ABSTRACT_BUFFER, QInfTextAbstractBuffer))
#define QINF_TEXT_ABSTRACT_BUFFER_CLASS(klass)         (G_TYPE_CHECK_CLASS_CAST((klass), QINF_TEXT_TYPE_ABSTRACT_BUFFER, QInfTextAbstractBufferClass))
#define QINF_TEXT_IS_ABSTRACT_BUFFER(obj)              (G_TYPE_CHECK_INSTANCE_TYPE((obj), QINF_TEXT_TYPE_ABSTRACT_BUFFER))
#define QINF_TEXT_IS_ABSTRACT_BUFFER_CLASS(klass)      (G_TYPE_CHECK_CLASS_TYPE((klass), QINF_TEXT_TYPE_ABSTRACT_BUFFER))
#define QINF_TEXT_ABSTRACT_BUFFER_GET_CLASS(obj)       (G_TYPE_INSTANCE_GET_CLASS((obj), QINF_TEXT_TYPE_ABSTRACT_BUFFER, QInfTextAbstractBufferClass))

typedef struct _QInfTextAbstractBufferClass QInfTextAbstractBufferClass;
typedef struct _QInfTextAbstractBuffer QInfTextAbstractBuffer;

struct _QInfTextAbstractBufferClass
{
    GObjectClass parent_class;
};

struct _QInfTextAbstractBuffer
{
    GObject parent;
};

GType
qinf_text_abstract_buffer_get_type(void) G_GNUC_CONST;

QInfTextAbstractBuffer*
qinf_text_abstract_buffer_new(const gchar* encoding);

G_END_DECLS

#endif
