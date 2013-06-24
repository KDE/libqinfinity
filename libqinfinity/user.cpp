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
#include "qgsignal.h"

#include <libinfinity/adopted/inf-adopted-user.h>

#include <QDebug>
#include <QColor>

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

unsigned int User::id() const
{
    return inf_user_get_id( INF_USER(gobject()) );
}

QString User::name() const
{
    return inf_user_get_name( INF_USER(gobject()) );
}

const QColor User::color() const
{
    // This uses the Y'UV color model, for colors of predictable brightness
    const uint hash = qHash(name());
    const uint hue = ((hash % 19) * 4129) % 360;
    const uint sat = 180 + ((hash % 2814) * 11) % 75;
    const uint val = 180 + ((hash % 3741) * 17) % 75;
    QColor color = QColor::fromHsv(hue, sat, val);
    while ( 0.299*color.red() + 0.587*color.green() + 0.114*color.blue() < 0.65*255 ) {
        color = color.lighter(120);
    }
    return color;
}

User::Status User::status() const
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
    InfUserStatus ret = INF_USER_UNAVAILABLE;
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
    new QGSignal( this, "notify::status",
        G_CALLBACK(User::status_changed_cb), this, this );
}

void User::emitStatusChanged()
{
    emit(statusChanged());
}

void User::status_changed_cb( InfUser *instance,
    const char *property,
    void *user_data )
{
    static_cast<User*>(user_data)->emitStatusChanged();
}

}

