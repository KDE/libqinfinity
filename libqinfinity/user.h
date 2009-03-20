#ifndef QINFINITY_USER_H
#define QINFINITY_USER_H

#include "qgobject.h"

#include <libinfinity/common/inf-user.h>

namespace QInfinity
{

class User
    : public QGObject
{

    public:
        enum Status
        {
            Active,
            Inactive,
            Unavailable
        };

        static User *create( InfUser *infUser,
            QObject *parent = 0 );

        unsigned int id();
        QString name();
        Status status();

    protected:
        static Status convertStatus( InfUserStatus status );
        static InfUserStatus convertStatus( Status status );

        User( InfUser *infUser,
           QObject *parent = 0 );

};

}

#endif

