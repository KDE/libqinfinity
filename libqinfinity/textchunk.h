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
            const QString &text,
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

