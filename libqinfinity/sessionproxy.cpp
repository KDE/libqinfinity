#include "sessionproxy.h"
#include "session.h"

#include <libinfinity/client/infc-session-proxy.h>

namespace QInfinity
{

SessionProxy::SessionProxy( InfSessionProxy *infProxy,
    QObject *parent )
    : QObject( parent )
    , QGObject( G_OBJECT(infProxy) )
{
}

SessionProxy::SessionProxy( const SessionProxy &other,
    QObject *parent )
    : QObject( parent )
    , QGObject( other.gobject() )
{
}

InfcUserRequest *SessionProxy::joinUser( const GParameter *params,
    unsigned int n_params,
    GError **error )
{
    return infc_session_proxy_join_user( INFC_SESSION_PROXY(gobject()),
        params,
        n_params,
        error );
}

Session *SessionProxy::session() const
{
    return new Session( infc_session_proxy_get_session( INFC_SESSION_PROXY(gobject()) ) );
}

}

