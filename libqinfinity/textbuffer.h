#ifndef QINFINITY_TEXT_BUFFER_H
#define QINFINITY_TEXT_BUFFER_H

#include "buffer.h"

#include <libinftext/inf-text-buffer.h>

namespace QInfinity
{

class TextChunk;

class TextBuffer
    : public Buffer
{

    public:
        static TextBuffer *create( InfTextBuffer *infBuffer,
            QObject *parent = 0 );
        
        QString encoding();
        unsigned int length();
        TextChunk *slice( unsigned int pos,
            unsigned int len );
        void insertText( unsigned int pos,
            const QString &text,
            unsigned int user );
        void insertChunk( unsigned int pos,
            const TextChunk &chunk,
            unsigned int user );
        void eraseText( unsigned int pos,
            unsigned int len,
            unsigned int user );

    protected:
        TextBuffer( InfTextBuffer *infBuffer,
            QObject *parent = 0 );

};

}

#endif

