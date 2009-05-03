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

#ifndef QINFINITY_TEXT_CHUNK_H
#define QINFINITY_TEXT_CHUNK_H

#include <libinftext/inf-text-chunk.h>

#include <QString>

namespace QInfinity
{

/**
 * @brief Represents a chunk of text in a TextBuffer
 */
class TextChunk
{

    public:
        TextChunk( InfTextChunk *chunk,
            bool own_chunk = false );
        TextChunk( const QString &encoding );
        TextChunk( const TextChunk &other );
        ~TextChunk();

        QString encoding() const;
        unsigned int length() const;
        QByteArray text() const;

        void insertText( unsigned int offset,
            const QByteArray &data,
            unsigned int length,
            unsigned int author );
        void insertChunk( unsigned int offset,
            const TextChunk &chunk );
        void erase( unsigned int begin,
            unsigned int end );
        InfTextChunk *infChunk() const;

    private:
        InfTextChunk *m_infChunk;
        bool m_own_chunk;

};

}

#endif

