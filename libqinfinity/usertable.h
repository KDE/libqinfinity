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

