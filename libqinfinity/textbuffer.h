#ifndef QINFINITY_TEXT_BUFFER_H
#define QINFINITY_TEXT_BUFFER_H

#include "qgobject.h"

namespace QInfinity
{

class TextBuffer
    : public QGObject
{

    public:
        TextBuffer( InfTextBuffer *infBuffer );

};

}

#endif

