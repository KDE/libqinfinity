#include "sessionproxy.h"
#include "session.h"
#include "wrapperstore.h"

#include <libinfinity/client/infc-session-proxy.h>

namespace QInfinity
{

QPointer<SessionProxy> SessionProxy::wrap( InfcSessionProxy *infObject,
    QObject *parent,
    bool own_gobject )
{
    QGObject *wrapptr = WrapperStore::getWrapper( G_OBJECT(infObject), own_gobject );
    if( wrapptr)
        return dynamic_cast<SessionProxy*>(wrapptr);
    SessionProxy *wrapper = new SessionProxy( infObject, parent, own_gobject );
    return wrapper;
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
    return Session::wrap( infc_session_proxy_get_session( INFC_SESSION_PROXY(gobject()) ) );
}

SessionProxy::SessionProxy( InfcSessionProxy *infProxy,
    QObject *parent,
       bool own_gobject )
    : QGObject( G_OBJECT(infProxy), parent, own_gobject )
{
}

}

