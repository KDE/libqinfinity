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

#ifndef QINFINITY_USER_TABLE_H
#define QINFINITY_USER_TABLE_H

#include "qgobject.h"
#include "user.h"

#include <libinfinity/common/inf-user-table.h>

#include <QPointer>
#include <QList>

namespace QInfinity
{

class UserTable
    : public QGObject
{
    Q_OBJECT;

    public:
        static QPointer<UserTable> wrap( InfUserTable *infUserTable,
            QObject *parent = 0,
            bool own_gobject = false );

        UserTable( QObject *parent = 0 );
        QPointer<User> lookupUser( unsigned int id );
        QPointer<User> lookupUser( const QString &name );
        QList<QPointer<User> > localUsers();
        QList<QPointer<User> > users();
        QList<QPointer<User> > activeUsers();

    Q_SIGNALS:
        void localUserAdded( User *user );
        void localUserRemoved( User *user );
        void userAdded( User *user );
        void userRemoved( User *user );

    protected:
        UserTable( InfUserTable *infUserTable,
            QObject *parent = 0,
            bool own_gobject = false );
    
    private:
        static void addLocalUserCb( InfUserTable *infUserTable,
            InfUser *infUser,
            void *user_data );
        static void removeLocalUserCb( InfUserTable *infUserTable,
            InfUser *infUser,
            void *user_data );
        static void addUserCb( InfUserTable *infUserTable,
            InfUser *infUser,
            void *user_data );
        static void removeUserCb( InfUserTable *infUserTable,
            InfUser *infUser,
            void *user_data );

        void emitLocalUserAdded( User *user );
        void emitLocalUserRemoved( User *user );
        void emitUserAdded( User *user );
        void emitUserRemoved( User *user );

        void setupSignals();

};

}

#endif

