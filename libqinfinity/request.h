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

#ifndef QINFINITY_REQUEST_H
#define QINFINITY_REQUEST_H

#include "qgobject.h"

#include <libinfinity/common/inf-request.h>

#include <glib.h>

namespace QInfinity
{

class Request
    : public QGObject
{
    Q_OBJECT

    public:
        // TODO: This should really use a wrap method
        Request( InfRequest *infRequest,
            QObject *parent = 0 );

    Q_SIGNALS:
        void failed( GError *error );
    
    private:
        void setupSignals();
        void signalFailed( GError *error );

        static void signalFailed_cb( InfRequest *request,
            GError *error,
            void *user_data );

};

}

#endif

