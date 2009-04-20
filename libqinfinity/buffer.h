#ifndef QINFINITY_BUFFER_H
#define QINFINITY_BUFFER_H

#include "qgobject.h"

#include <libinfinity/common/inf-buffer.h>

#include <QPointer>

namespace QInfinity
{

/**
 * @brief A base buffer for collaborative editing.
 *
 * You probably want to look at a subclass of this,
 * such as TextBuffer or AbstractTextBuffer.
 */
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

