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

#include "adopteduser.h"
#include "wrapperstore.h"

#include <libinfinity/adopted/inf-adopted-user.h>

#include <QDebug>

#include "adopteduser.moc"

namespace QInfinity
{

QPointer<AdoptedUser> AdoptedUser::wrap( InfAdoptedUser *infObject,
    QObject *parent,
    bool own_gobject )
{
    QGObject *wrapptr = WrapperStore::getWrapper( G_OBJECT(infObject), own_gobject );
    if( wrapptr)
        return dynamic_cast<AdoptedUser*>(wrapptr);
    // Make sure we instantiate the most specific user type
    AdoptedUser *wrapper;
    wrapper = new AdoptedUser( infObject, parent, own_gobject );
    return wrapper;
}

AdoptedUser::AdoptedUser( InfAdoptedUser *infUser,
    QObject *parent,
    bool own_gobject )
    : User( INF_USER(infUser), parent, own_gobject )
{
}

}
