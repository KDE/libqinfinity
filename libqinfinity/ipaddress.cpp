#include "ipaddress.h"

namespace QInfinity
{

IpAddress::IpAddress( unsigned int raw_address )
    : QGObject()
{
    InfIpAddress *infObj;

    infObj = inf_ip_address_new_raw4( raw_address );
    setGobject( G_OBJECT(infObj) );
}

IpAddress::IpAddress( const char *address_string )
    : QGObject()
{
    InfIpAddress *infObj;

    infObj = inf_ip_address_new_from_string( address_string );
    setGobject( G_OBJECT(infObj) );
}

const char *IpAddress::toString()
{
    return inf_ip_address_to_string( (const InfIpAddress*)(gobject()) );
}

}

