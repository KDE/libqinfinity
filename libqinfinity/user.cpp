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

#include "user.h"
#include "wrapperstore.h"
#include "adopteduser.h"

#include <libinfinity/adopted/inf-adopted-user.h>

#include <QDebug>

#include "user.moc"

namespace QInfinity
{

QPointer<User> User::wrap( InfUser *infObject,
    QObject *parent,
    bool own_gobject )
{
    QGObject *wrapptr = WrapperStore::getWrapper( G_OBJECT(infObject), own_gobject );
    if( wrapptr)
        return dynamic_cast<User*>(wrapptr);
    // Make sure we instantiate the most specific user type
    User *wrapper;
    if( !INF_ADOPTED_IS_USER(infObject) )
    {
        wrapper = AdoptedUser::wrap( INF_ADOPTED_USER(infObject), parent, own_gobject );
    }
    else
    {
        wrapper = new User( infObject, parent, own_gobject );
    }
    return wrapper;
}

unsigned int User::id()
{
    return inf_user_get_id( INF_USER(gobject()) );
}

QString User::name()
{
    return inf_user_get_name( INF_USER(gobject()) );
}

User::Status User::status()
{
    return User::convertStatus( inf_user_get_status( INF_USER(gobject()) ) );
}

User::Status User::convertStatus( InfUserStatus status )
{
    Status ret;
    switch( status )
    {
        case INF_USER_ACTIVE:
            ret = Active;
            break;
        case INF_USER_INACTIVE:
            ret = Inactive;
            break;
        default:
            ret = Unavailable;
    }
    return ret;
}

InfUserStatus User::convertStatus( Status status )
{
    InfUserStatus ret;
    switch( status )
    {
        case Active:
            ret = INF_USER_ACTIVE;
            break;
        case Inactive:
            ret = INF_USER_INACTIVE;
            break;
        case Unavailable:
            ret = INF_USER_UNAVAILABLE;
    }
    return ret;
}

User::User( InfUser *infUser,
    QObject *parent,
    bool own_gobject )
    : QGObject( G_OBJECT(infUser), parent, own_gobject )
{
}

}

