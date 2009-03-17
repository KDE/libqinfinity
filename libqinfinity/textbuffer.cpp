#include "textbuffer.h"
#include "textchunk.h"
#include "wrapperstore.h"

namespace QInfinity
{

TextBuffer *TextBuffer::create( InfTextBuffer *infBuffer,
    QObject *parent )
{
    WrapperStore *store = WrapperStore::instance();
    TextBuffer *buffer = dynamic_cast<TextBuffer*>(store->findWrapper( G_OBJECT(infBuffer) ));
    if( !buffer )
        buffer = new TextBuffer( infBuffer, parent );
    return buffer;
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
    QObject *parent )
    : Buffer( INF_BUFFER(infBuffer), parent )
{
}

}

