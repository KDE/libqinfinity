#include "textchunk.h"

namespace QInfinity
{

TextChunk::TextChunk( const QString &encoding )
    : m_infChunk( inf_text_chunk_new( encoding.toAscii() ) )
{
}

TextChunk::TextChunk( const TextChunk &other )
{
    m_infChunk = inf_text_chunk_copy( other.infChunk() );
}

TextChunk::~TextChunk()
{
    inf_text_chunk_free( m_infChunk );
}

void TextChunk::insertText( unsigned int offset,
    const QString &text,
    unsigned int author )
{
    inf_text_chunk_insert_text( m_infChunk,
        offset, text.toAscii(),
        text.size(), text.length(),
        author );
}

InfTextChunk *TextChunk::infChunk() const
{
    return m_infChunk;
}

}

