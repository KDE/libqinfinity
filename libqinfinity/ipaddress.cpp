/*
 * Copyright 2009  Gregory Haynes <greg@greghaynes.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ipaddress.h"

#include <libinfinity/common/inf-ip-address.h>

namespace QInfinity
{

IpAddress::IpAddress( const QHostAddress &address )
    : m_gobject( inf_ip_address_new_from_string( address.toString().toUtf8() ) )
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

