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

#ifndef QINFINITY_USER_H
#define QINFINITY_USER_H

#include "qgobject.h"

#include <libinfinity/common/inf-user.h>

#include <QPointer>

namespace QInfinity
{

class User
    : public QGObject
{
    Q_OBJECT

    public:
        enum Status
        {
            Active,
            Inactive,
            Unavailable
        };

        static QPointer<User> wrap( InfUser *infUser,
            QObject *parent = 0,
            bool own_gobject = false );
        static Status convertStatus( InfUserStatus status );
        static InfUserStatus convertStatus( Status status );

        unsigned int id();
        QString name();
        Status status();
    
    Q_SIGNALS:
        void statusChanged();

    protected:
        User( InfUser *infUser,
            QObject *parent = 0,
            bool own_gobject = false );

    private:
        void emitStatusChanged();

        static void status_changed_cb( InfUser *instance,
            const char *property,
            void *user_data );
    
};

}

#endif

