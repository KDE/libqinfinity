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

#ifndef QINFINITY_USERREQUEST_H
#define QINFINITY_USERREQUEST_H

#include "request.h"
#include "user.h"

#include <QPointer>

#include <libinfinity/common/inf-user.h>
#include <libinfinity/client/infc-request.h>

namespace QInfinity
{

class UserRequest
    : public Request
{
    Q_OBJECT;

    public:
        UserRequest( InfRequest *infRequest,
            QObject *parent = 0 );

    Q_SIGNALS:
        void finished( QPointer<QInfinity::User> user );

    private:
        static void finished_cb( InfRequest* request,
                                 const InfRequestResult* result,
                                 const GError* error,
                                 void *user_data );

        void emit_finished( QPointer<QInfinity::User> user );

};

}

#endif
