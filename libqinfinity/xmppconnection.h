#ifndef QINFINITY_XMPP_CONNECTION_H
#define QINFINITY_XMPP_CONNECTION_H

#include "xmlconnection.h"

#include <libinfinity/common/inf-xmpp-connection.h>

#include <gnutls/gnutls.h>
#include <gsasl.h>

namespace QInfinity
{

class TcpConnection;

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
            const char *local_hostname,
            const char *remote_hostname,
            SecurityPolicy securityPolicy,
            gnutls_certificate_credentials_t cred = 0,
            Gsasl *sasl_context = 0,
            const char *sasl_mechanisms = 0,
               QObject *parent = 0 );

};

}

#endif

