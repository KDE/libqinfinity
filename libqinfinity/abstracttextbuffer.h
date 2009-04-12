#ifndef QINFINITY_ABSTRACT_TEXT_BUFFER_H
#define QINFINITY_ABSTRACT_TEXT_BUFFER_H

#include "textbuffer.h"

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

#define INF_TEXT_TYPE_ABSTRACT_BUFFER                 (inf_text_abstract_buffer_get_type())
#define INF_TEXT_ABSTRACT_BUFFER(obj)                 (G_TYPE_CHECK_INSTANCE_CAST((obj), INF_TEXT_TYPE_ABSTRACT_BUFFER, InfTextAbstractBuffer))
#define INF_TEXT_ABSTRACT_BUFFER_CLASS(klass)         (G_TYPE_CHECK_CLASS_CAST((klass), INF_TEXT_TYPE_ABSTRACT_BUFFER, InfTextAbstractBufferClass))
#define INF_TEXT_IS_ABSTRACT_BUFFER(obj)              (G_TYPE_CHECK_INSTANCE_TYPE((obj), INF_TEXT_TYPE_ABSTRACT_BUFFER))
#define INF_TEXT_IS_ABSTRACT_BUFFER_CLASS(klass)      (G_TYPE_CHECK_CLASS_TYPE((klass), INF_TEXT_TYPE_ABSTRACT_BUFFER))
#define INF_TEXT_ABSTRACT_BUFFER_GET_CLASS(obj)       (G_TYPE_INSTANCE_GET_CLASS((obj), INF_TEXT_TYPE_ABSTRACT_BUFFER, InfTextAbstractBufferClass))

typedef struct _QInfTextAbstractBufferClass QInfTextAbstractBufferClass;
typedef struct _QInfTextAbstractBuffer QInfTextAbstractBuffer;

struct _QInfTextAbstractBufferClass
{
    GObjectClass *parent_class;
};

struct _QInfTextAbstractBuffer
{
    GObject *parent;
    QInfinity::AbstractTextBuffer *wrapper;
};

G_END_DECLS

#endif
