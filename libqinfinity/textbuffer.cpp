#include "textbuffer.h"
#include "textchunk.h"
#include "wrapperstore.h"

namespace QInfinity
{

QPointer<TextBuffer> TextBuffer::wrap( InfTextBuffer *infObject,
    QObject *parent,
    bool own_gobject )
{
    QGObject *wrapptr = WrapperStore::getWrapper( G_OBJECT(infObject), own_gobject );
    if( wrapptr)
        return dynamic_cast<TextBuffer*>(wrapptr);
    TextBuffer *wrapper = new TextBuffer( infObject, parent, own_gobject );
    return wrapper;
}

QString TextBuffer::encoding()
{
    return inf_text_buffer_get_encoding( INF_TEXT_BUFFER(gobject()) );
}

unsigned int TextBuffer::length()
{
    return inf_text_buffer_get_length( INF_TEXT_BUFFER(gobject()) );
}

TextChunk *TextBuffer::slice( unsigned int pos,
    unsigned int len )
{
    return new TextChunk( inf_text_buffer_get_slice( INF_TEXT_BUFFER(gobject()),
        pos, len ) );
}

TextBuffer::TextBuffer( InfTextBuffer *infBuffer,
    QObject *parent,
    bool own_gobject )
    : Buffer( INF_BUFFER(infBuffer), parent, own_gobject )
{
}

}

