#include "ipaddress.h"

namespace QInfinity
{

IpAddress::IpAddress( unsigned int raw_address )
    : m_gobject( inf_ip_address_new_raw4( raw_address ) )
{
}

IpAddress::IpAddress( const char *address_string )
    : m_gobject( inf_ip_address_new_from_string( address_string ) )
{
}

IpAddress::~IpAddress()
{
    inf_ip_address_free(m_gobject);
}

const char *IpAddress::toString()
{
    return inf_ip_address_to_string( (const InfIpAddress*)(gobject()) );
}

InfIpAddress *IpAddress::gobject() const
{
    return m_gobject;
}

}

