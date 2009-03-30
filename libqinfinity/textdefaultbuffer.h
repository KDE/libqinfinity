#ifndef QINFINITY_TEXT_DEFAULT_BUFFER
#define QINFINITY_TEXT_DEFAULT_BUFFER

#include "textbuffer.h"

#include <QString>

namespace QInfinity
{

class TextDefaultBuffer
    : public TextBuffer
{

    public:
        TextDefaultBuffer( QString encoding = "UTF-8",
            QObject *parent = 0 );

};

}

#endif

