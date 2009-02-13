#ifndef QINFINITY_BUFFER_H
#define QINFINITY_BUFFER_H

#include "qgobject.h"

#include <libinfinity/common/inf-buffer.h>

namespace QInfinity
{

class Buffer
    : public QGObject
{

    public:
        Buffer( InfBuffer *buffer,
            QObject *parent = 0 );

};

}

#endif

