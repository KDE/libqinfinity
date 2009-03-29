#include "textchunk.h"

namespace QInfinity
{

TextChunk::TextChunk( InfTextChunk *infChunk,
    bool own_chunk )
    : m_infChunk( infChunk )
    , m_own_chunk( own_chunk )
{
}

TextChunk::TextChunk( const QString &encoding )
    : m_infChunk( inf_text_chunk_new( encoding.toAscii() ) )
    , m_own_chunk( true )
{
}

TextChunk::TextChunk( const TextChunk &other )
{
    m_infChunk = inf_text_chunk_copy( other.infChunk() );
    m_own_chunk = true;
}

TextChunk::~TextChunk()
{
    if( m_own_chunk )
        inf_text_chunk_free( m_infChunk );
}

QString TextChunk::encoding() const
{
    return inf_text_chunk_get_encoding( infChunk() );
}

unsigned int TextChunk::length() const
{
    return inf_text_chunk_get_length( infChunk() );
}

QByteArray TextChunk::text() const
{
    void *data;
    gsize size;
    data = inf_text_chunk_get_text( infChunk(), &size );
    return QByteArray( (const char*)data, size );
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

void TextChunk::insertChunk( unsigned int offset,
    const TextChunk &chunk )
{
    inf_text_chunk_insert_chunk( infChunk(), offset,
        chunk.infChunk() );
}

void TextChunk::erase( unsigned int begin,
    unsigned int end )
{
    inf_text_chunk_erase( infChunk(),
        begin, end );
}

InfTextChunk *TextChunk::infChunk() const
{
    return m_infChunk;
}

}

