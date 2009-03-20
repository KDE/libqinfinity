#ifndef QINFINITY_USER_TABLE_H
#define QINFINITY_USER_TABLE_H

#include "qgobject.h"

#include <libinfinity/common/inf-user-table.h>

namespace QInfinity
{

class UserTable
    : public QGObject
{

    public:
        static UserTable *create( InfUserTable *infUserTable,
            QObject *parent = 0 );

        UserTable( QObject *parent = 0 );

    protected:
        UserTable( InfUserTable *infUserTable,
            QObject *parent = 0 );

};

}

#endif

