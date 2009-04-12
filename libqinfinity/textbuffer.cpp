#include "textbuffer.h"
#include "textchunk.h"
#include "user.h"
#include "wrapperstore.h"

#include "textbuffer.moc"

#include <libinftext/inf-text-chunk.h>

#include <QDebug>

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

TextBuffer::~TextBuffer()
{
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

void TextBuffer::insertText( unsigned int pos,
    const QByteArray &data,
    unsigned int length,
    User *user )
{
    inf_text_buffer_insert_text( INF_TEXT_BUFFER(gobject()),
        pos, data.data(), data.length(), length,
        INF_USER(user->gobject()) );
}

void TextBuffer::eraseText( unsigned int pos,
    unsigned int len,
    User *user )
{
    inf_text_buffer_erase_text( INF_TEXT_BUFFER(gobject()),
        pos, len, INF_USER(user->gobject()) );
}

void TextBuffer::insertChunk( unsigned int pos,
    const TextChunk &chunk,
    User *user )
{
    inf_text_buffer_insert_chunk( INF_TEXT_BUFFER(gobject()),
        pos, chunk.infChunk(),
        INF_USER(user->gobject()) );
}

TextBuffer::TextBuffer( InfTextBuffer *infBuffer,
    QObject *parent,
    bool own_gobject )
    : Buffer( INF_BUFFER(infBuffer), parent, own_gobject )
{
    erase_text_handler = g_signal_connect_after( gobject(),
        "erase-text", G_CALLBACK(TextBuffer::text_erased_cb),
        this );
    insert_text_handler = g_signal_connect_after( gobject(),
        "insert-text", G_CALLBACK(TextBuffer::text_inserted_cb),
        this );
}

void TextBuffer::text_erased_cb( InfTextBuffer *infTextBuffer,
    unsigned int offset,
    unsigned int len,
    InfUser *user,
    void *user_data )
{
    TextBuffer *textBuffer = static_cast<TextBuffer*>(user_data);
    textBuffer->emitTextErased( offset, len, user );
}

void TextBuffer::text_inserted_cb( InfTextBuffer *infTextBuffer,
    unsigned int offset,
    InfTextChunk *textChunk,
    InfUser *user,
    void *user_data )
{
    TextBuffer *textBuffer = static_cast<TextBuffer*>(user_data);
    textBuffer->emitTextInserted( offset, textChunk, user );
}

void TextBuffer::emitTextErased( unsigned int offset,
    unsigned int len,
    InfUser *user )
{
    emit( textErased( offset, len, User::wrap( user ) ) );
}

void TextBuffer::emitTextInserted( unsigned int offset,
    InfTextChunk *textChunk,
    InfUser *user )
{
    emit( textInserted( offset, TextChunk( textChunk ), User::wrap( user ) ) );
}

}

