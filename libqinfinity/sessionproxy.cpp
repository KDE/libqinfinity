#include "sessionproxy.h"

namespace QInfinity
{

SessionProxy::SessionProxy( InfSessionProxy *infProxy )
    : QGObject( G_OBJECT(infProxy) )
{
}

SessionProxy::SessionProxy( const SessionProxy &other )
    : QGObject( other.gobject() )
{
}

}

