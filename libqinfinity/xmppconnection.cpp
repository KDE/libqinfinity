#include "xmppconnection.h"
#include "tcpconnection.h"

#include "xmppconnection.moc"

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
    gnutls_certificate_credentials_t cred,
    Gsasl *sasl_context,
    const char *sasl_mechanisms,
       QObject *parent,
    bool own_gobject )
    : XmlConnection( INF_XML_CONNECTION(inf_xmpp_connection_new(
        INF_TCP_CONNECTION(tcpConnection.gobject()),
        XmppConnection::siteToInf( site ),
        local_hostname.toAscii(),
        remote_hostname.toAscii(),
        XmppConnection::securityPolicyToInf( securityPolicy ),
        cred,
        sasl_context,
        sasl_mechanisms )), parent, own_gobject )
{
}

}

