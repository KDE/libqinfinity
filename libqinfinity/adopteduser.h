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

#ifndef QINFINITY_ADOPTED_USER_H
#define QINFINITY_ADOPTED_USER_H

#include "user.h"

typedef struct _InfAdoptedUser InfAdoptedUser;

namespace QInfinity
{

class AdoptedUser
    : public User
{
    Q_OBJECT

    public:
        static QPointer<AdoptedUser> wrap( InfAdoptedUser *infUser,
            QObject *parent = 0,
            bool own_gobject = false );

    protected:
        AdoptedUser( InfAdoptedUser *infUser,
            QObject *parent = 0,
            bool own_gobject = false );

};

}

#endif
