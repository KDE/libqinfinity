#include "ipaddress.h"

namespace QInfinity
{

IpAddress::IpAddress( const QHostAddress &address )
    : m_gobject( inf_ip_address_new_from_string( address.toString().toAscii() ) )
{
}

IpAddress::IpAddress( quint32 raw_address )
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

QString IpAddress::toString()
{
    QString str;
    char *c_str; 

    c_str = inf_ip_address_to_string( (const InfIpAddress*)(gobject()) );
    str = c_str;
    g_free( c_str );
    return str;
}

InfIpAddress *IpAddress::gobject() const
{
    return m_gobject;
}

}

