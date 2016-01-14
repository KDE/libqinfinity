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

#include "textbuffer.h"
#include "textchunk.h"
#include "user.h"
#include "wrapperstore.h"



#include <libinftext/inf-text-chunk.h>

#include <QTextCodec>
#include <QTextEncoder>
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

QTextCodec *TextBuffer::codec() const
{
    return m_codec;
}

QTextEncoder *TextBuffer::encoder() const
{
    return m_encoder;
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
    // TODO test me, I don't think this is used anywhere in kobby
    QInfinity::TextChunk chunk( encoding() );
    chunk.insertText( 0, data, data.length(), user->id() );
    inf_text_buffer_text_inserted( INF_TEXT_BUFFER(gobject()),
        pos, chunk.infChunk(), INF_USER(user->gobject()) );
}

void TextBuffer::eraseText( unsigned int pos,
    unsigned int len,
    User *user )
{
    qDebug() << "erasing text:" << slice(pos, len)->text() << pos << len;
    inf_text_buffer_text_erased( INF_TEXT_BUFFER(gobject()),
        pos, slice(pos, len)->infChunk(), INF_USER(user->gobject()) );
    inf_text_buffer_erase_text( INF_TEXT_BUFFER(gobject()),
        pos, len, INF_USER(user->gobject()) );
}

void TextBuffer::insertChunk( unsigned int pos,
    const TextChunk &chunk,
    User *user )
{
    InfTextBufferIface* iface = INF_TEXT_BUFFER_GET_IFACE(INF_TEXT_BUFFER(gobject()));
    inf_text_buffer_text_inserted( INF_TEXT_BUFFER(gobject()),
        pos, chunk.infChunk(), INF_USER(user->gobject()) );
    inf_text_buffer_insert_chunk( INF_TEXT_BUFFER(gobject()),
        pos, chunk.infChunk(),
        INF_USER(user->gobject()) );
}

TextBuffer::TextBuffer( InfTextBuffer *infBuffer,
    QObject *parent,
    bool own_gobject )
    : Buffer( INF_BUFFER(infBuffer), parent, own_gobject )
    , m_codec( 0 )
    , m_encoder( 0 )
{
    m_codec = QTextCodec::codecForName( encoding().toUtf8() );
    if( m_codec )
        m_encoder = m_codec->makeEncoder();
    erase_text_handler = g_signal_connect_after( gobject(),
        "text-erased", G_CALLBACK(TextBuffer::text_erased_cb),
        this );
    insert_text_handler = g_signal_connect_after( gobject(),
        "text-inserted", G_CALLBACK(TextBuffer::text_inserted_cb),
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

