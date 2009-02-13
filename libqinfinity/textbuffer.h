#ifndef QINFINITY_TEXT_BUFFER_H
#define QINFINITY_TEXT_BUFFER_H

#include "buffer.h"

#include <libinftext/inf-text-buffer.h>

namespace QInfinity
{

class TextBuffer
    : public Buffer
{

    public:
        static TextBuffer *create( InfTextBuffer *infBuffer,
            QObject *parent = 0 );
        
        TextBuffer( QString encoding );
    protected:
        TextBuffer( InfTextBuffer *infBuffer,
            QObject *parent = 0 );

};

}

#endif

