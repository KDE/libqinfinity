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

#ifndef QINFINITY_TEXT_BUFFER_H
#define QINFINITY_TEXT_BUFFER_H

#include "buffer.h"

#include <libinfinity/common/inf-user.h>
#include <libinftext/inf-text-buffer.h>

#include <QPointer>

class QTextCodec;
class QTextEncoder;

namespace QInfinity
{

class TextChunk;
class User;

class TextBuffer
    : public Buffer
{
    Q_OBJECT;

    public:
        static QPointer<TextBuffer> wrap( InfTextBuffer *infBuffer,
            QObject *parent = 0,
            bool own_gobject = false );

        ~TextBuffer();
        
        QString encoding();
        QTextCodec *codec() const;
        QTextEncoder *encoder() const;
        unsigned int length();
        TextChunk *slice( unsigned int pos,
            unsigned int len );
        void insertText( unsigned int pos,
            const QByteArray &data,
            unsigned int len,
            User *user );
        void insertChunk( unsigned int pos,
            const TextChunk &chunk,
            User *user );
        void eraseText( unsigned int pos,
            unsigned int len,
            User *user );

    Q_SIGNALS:
        void textErased( unsigned int offset,
            unsigned int len,
            QPointer<QInfinity::User> user );
        void textInserted( unsigned int offset,
            const QInfinity::TextChunk &text,
            QPointer<QInfinity::User> user );

    protected:
        TextBuffer( InfTextBuffer *infBuffer,
            QObject *parent = 0,
            bool own_gobject = false );

    private:
        static void text_erased_cb( InfTextBuffer *infTextBuffer,
            unsigned int offset,
            unsigned int len,
            InfUser *user,
            void *user_data );
        static void text_inserted_cb( InfTextBuffer *infTextBuffer,
            unsigned int offset,
            InfTextChunk *textChunk,
            InfUser *user,
            void *user_data );

        void emitTextErased( unsigned int offset,
            unsigned int len,
            InfUser *user );
        void emitTextInserted( unsigned int offset,
            InfTextChunk *textChunk,
            InfUser *user );

        unsigned long erase_text_handler;
        unsigned long insert_text_handler;
        QTextCodec *m_codec;
        QTextEncoder *m_encoder;

};

}

#endif

