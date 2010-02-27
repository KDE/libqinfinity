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

#ifndef QINFINITY_ADOPTED_SESSION_H
#define QINFINITY_ADOPTED_SESSION_H

#include "session.h"

typedef struct _InfAdoptedSession InfAdoptedSession;

namespace QInfinity
{

class AdoptedUser;

class AdoptedSession
    : public Session
{

    public:
        /**
         * @brief Issue an undo request.
         */
        void undo( AdoptedUser &user,
            int count );
        /**
         * @brief Issue a redo request.
         */
        void redo( AdoptedUser &user,
            int count );

    protected:
        AdoptedSession( InfAdoptedSession *infSession,
            QObject *parent = 0,
            bool own_gobj = false );

};

}

#endif
