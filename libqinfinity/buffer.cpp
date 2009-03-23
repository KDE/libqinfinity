#include "buffer.h"
#include "wrapperstore.h"

namespace QInfinity
{

QPointer<Buffer> Buffer::wrap( InfBuffer *infBuffer,
    QObject *parent,
    bool own_gobject )
{
    QGObject *wrapptr = WrapperStore::getWrapper( G_OBJECT(infBuffer), own_gobject );
    if( wrapptr)
        return dynamic_cast<Buffer*>(wrapptr);
    Buffer *buffer = new Buffer( infBuffer, parent, own_gobject );
    return buffer;
}

Buffer::Buffer( InfBuffer *buffer,
    QObject *parent,
    bool own_gobject )
    : QGObject( G_OBJECT(buffer), parent, own_gobject )
{
}

}

