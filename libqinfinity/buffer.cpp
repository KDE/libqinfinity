#include "buffer.h"
#include "wrapperstore.h"

namespace QInfinity
{

Buffer *Buffer::create( InfBuffer *infBuffer )
{
    WrapperStore *store = WrapperStore::instance();
    Buffer *buffer = dynamic_cast<Buffer*>(store->findWrapper( G_OBJECT(infBuffer) ));
    if( !buffer )
        return new Buffer( infBuffer );
    return buffer;
}

Buffer::Buffer( InfBuffer *buffer,
    QObject *parent )
    : QGObject( G_OBJECT(buffer), parent )
{
}

}

