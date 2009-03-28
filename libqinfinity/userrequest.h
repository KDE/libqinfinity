#ifndef QINFINITY_USERREQUEST_H
#define QINFINITY_USERREQUEST_H

#include "request.h"
#include "user.h"

#include <QPointer>

#include <libinfinity/common/inf-user.h>
#include <libinfinity/client/infc-user-request.h>

namespace QInfinity
{

class UserRequest
    : public Request
{
    Q_OBJECT;

    public:
        UserRequest( InfcUserRequest *infRequest,
            QObject *parent = 0 );

    Q_SIGNALS:
        void finished( QPointer<QInfinity::User> user );

    private:
        static void finished_cb( InfcUserRequest *infcUserRequest,
            InfUser *user,
            void *user_data );

        void emit_finished( QPointer<QInfinity::User> user );

        unsigned long finished_handler;

};

}

#endif
