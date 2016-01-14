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

#include "xmppconnection.h"
#include "tcpconnection.h"
#include "certificatecredentials.h"

#include <libinfinity/common/inf-simulated-connection.h>



namespace QInfinity
{

InfXmppConnectionSite XmppConnection::siteToInf( Site site )
{
    switch( site )
    {
        case Server:
            return INF_XMPP_CONNECTION_SERVER;
        default:
            return INF_XMPP_CONNECTION_CLIENT;
    }
}

InfXmppConnectionSecurityPolicy XmppConnection::securityPolicyToInf( SecurityPolicy policy )
{
    switch( policy )
    {
        case OnlyUnsecured:
            return INF_XMPP_CONNECTION_SECURITY_ONLY_UNSECURED;
        case OnlyTls:
            return INF_XMPP_CONNECTION_SECURITY_ONLY_TLS;
        case PreferUnsecured:
            return INF_XMPP_CONNECTION_SECURITY_BOTH_PREFER_UNSECURED;
        default:
            return INF_XMPP_CONNECTION_SECURITY_BOTH_PREFER_TLS;
    }
}

XmppConnection::XmppConnection( TcpConnection &tcpConnection,
    Site site,
    const QString &local_hostname,
    const QString &remote_hostname,
    SecurityPolicy securityPolicy,
    CertificateCredentials *cred,
    InfSaslContext *sasl_context,
    const char *sasl_mechanisms,
       QObject *parent,
    bool own_gobject )
    : XmlConnection( INF_XML_CONNECTION(inf_xmpp_connection_new(
        INF_TCP_CONNECTION(tcpConnection.gobject()),
        XmppConnection::siteToInf( site ),
        local_hostname.toUtf8(),
        remote_hostname.toUtf8(),
        XmppConnection::securityPolicyToInf( securityPolicy ),
        cred ? (InfCertificateCredentials*)cred->gobject(): 0,
        sasl_context,
        sasl_mechanisms )), parent, own_gobject )
{
}

XmppConnection::XmppConnection(QObject* parent)
    : XmlConnection(INF_XML_CONNECTION(inf_simulated_connection_new()), parent, true)
{
    qDebug() << "creating new *simulated* Xmpp connection";
}

void XmppConnection::connectSimulatedConnection(XmppConnection* other)
{
    Q_ASSERT( INF_IS_SIMULATED_CONNECTION(gobject()) );
    Q_ASSERT( INF_IS_SIMULATED_CONNECTION(other->gobject()) );
    qDebug() << "connecting simulated connections" << gobject() << other->gobject();
    inf_simulated_connection_connect( INF_SIMULATED_CONNECTION(gobject()),
                                      INF_SIMULATED_CONNECTION(other->gobject()) );
}

}

