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

QPointer<Session> SessionProxy::session() const
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

