#include "buffer.h"

namespace QInfinity
{

Buffer::Buffer( InfBuffer *buffer,
    QObject *parent )
    : QGObject( G_OBJECT(buffer), parent )
{
}

}

