#ifndef QINFINITY_USER_TABLE_H
#define QINFINITY_USER_TABLE_H

#include "qgobject.h"

#include <libinfinity/common/inf-user-table.h>

#include <QPointer>

namespace QInfinity
{

class UserTable
    : public QGObject
{

    public:
        static QPointer<UserTable> wrap( InfUserTable *infUserTable,
            QObject *parent = 0,
            bool own_gobject = false );

        UserTable( QObject *parent = 0 );

    protected:
        UserTable( InfUserTable *infUserTable,
            QObject *parent = 0,
            bool own_gobject = false );

};

}

#endif

