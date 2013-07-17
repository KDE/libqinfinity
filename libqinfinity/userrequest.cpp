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

#include "userrequest.h"
#include "qgsignal.h"
#include "adopteduser.h"

#include <libinfinity/adopted/inf-adopted-session.h>

#include "userrequest.moc"

namespace QInfinity
{

UserRequest::UserRequest( InfcUserRequest *infRequest,
    QObject *parent )
    : Request( INFC_REQUEST( infRequest ), parent )
{
    new QGSignal( this, "finished",
        G_CALLBACK(UserRequest::finished_cb), this, this );
}

void UserRequest::finished_cb( InfcUserRequest *infcUserRequest,
    InfUser *user,
    void *user_data )
{
    UserRequest *userRequest = static_cast<UserRequest*>(user_data);
    QPointer<QInfinity::User> wrappedUser;
    if ( INF_ADOPTED_IS_USER(user) ) {
        wrappedUser = AdoptedUser::wrap( INF_ADOPTED_USER(user) );
    }
    else {
        wrappedUser = User::wrap( user );
    }
    userRequest->emit_finished( wrappedUser );
}

void UserRequest::emit_finished( QPointer<QInfinity::User> user )
{
    emit( finished( user ) );
}

}

