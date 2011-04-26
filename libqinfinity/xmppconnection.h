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

#ifndef QINFINITY_XMPP_CONNECTION_H
#define QINFINITY_XMPP_CONNECTION_H

#include "xmlconnection.h"

#include <libinfinity/common/inf-xmpp-connection.h>
#include <libinfinity/common/inf-sasl-context.h>

#include <gnutls/gnutls.h>

namespace QInfinity
{

class TcpConnection;
class CertificateCredentials;

class XmppConnection
    : public XmlConnection
{
    Q_OBJECT
    
    public:
        enum Site
        {
            Client,
            Server
        };

        enum SecurityPolicy
        {
            OnlyUnsecured,
            OnlyTls,
            PreferUnsecured,
            PreferTls
        };

        static InfXmppConnectionSite siteToInf( Site );
        static InfXmppConnectionSecurityPolicy securityPolicyToInf( SecurityPolicy );

        XmppConnection( TcpConnection &tcpConnection,
            Site site,
            const QString &local_hostname,
            const QString &remote_hostname,
            SecurityPolicy securityPolicy,
            CertificateCredentials *cred = 0,
            InfSaslContext *sasl_context = 0,
            const char *sasl_mechanisms = 0,
               QObject *parent = 0,
               bool own_gobject = true );

};

}

#endif

