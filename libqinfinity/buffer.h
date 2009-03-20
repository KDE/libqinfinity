#ifndef QINFINITY_BUFFER_H
#define QINFINITY_BUFFER_H

#include "qgobject.h"

#include <libinfinity/common/inf-buffer.h>

#include <QPointer>

namespace QInfinity
{

class Buffer
    : public QGObject
{

    public:
        static QPointer<Buffer> wrap( InfBuffer *buffer,
            QObject *parent = 0,
            bool own_gobject = false );

    protected:
        Buffer( InfBuffer *buffer,
            QObject *parent = 0,
            bool own_gobject = false );

};

}

#endif

