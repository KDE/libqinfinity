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

#include "adoptedsession.h"
#include "adopteduser.h"

#include <libinfinity/adopted/inf-adopted-session.h>

namespace QInfinity
{

void AdoptedSession::undo( AdoptedUser &user,
    int count )
{
    inf_adopted_session_undo( INF_ADOPTED_SESSION(gobject()),
        INF_ADOPTED_USER(user.gobject()), count );
}

void AdoptedSession::redo( AdoptedUser &user,
    int count )
{
    inf_adopted_session_redo( INF_ADOPTED_SESSION(gobject()),
        INF_ADOPTED_USER(user.gobject()), count );
}

AdoptedSession::AdoptedSession( InfAdoptedSession *infSession,
    QObject *parent,
    bool own_gobject )
    : Session( INF_SESSION(infSession), parent, own_gobject )
{
}

}
