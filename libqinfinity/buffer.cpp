#include "buffer.h"
#include "wrapperstore.h"

namespace QInfinity
{

QPointer<Buffer> Buffer::wrap( InfBuffer *infBuffer,
    QObject *parent )
{
    QGObject *wrapptr = WrapperStore::getWrapper( G_OBJECT(infBuffer) );
    if( wrapptr)
        return dynamic_cast<Buffer*>(wrapptr);
    Buffer *buffer = new Buffer( infBuffer, parent );
    WrapperStore::insertWrapper( G_OBJECT(infBuffer), buffer );
    return buffer;
}

Buffer::Buffer( InfBuffer *buffer,
    QObject *parent )
    : QGObject( G_OBJECT(buffer), parent )
{
}

}

