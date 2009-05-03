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

#ifndef QINFINITY_SESSION_PROXY_H
#define QINFINITY_SESSION_PROXY_H

#include "qgobject.h"

#include <QObject>
#include <QPointer>

typedef struct _InfcSessionProxy InfcSessionProxy;
typedef struct _InfSession InfSession;
typedef struct _InfcUserRequest InfcUserRequest;
typedef struct _GParameter GParameter;

namespace QInfinity
{

class Session;

/**
 * @brief Used for retrieving newly created sessions.
 */
class SessionProxy
    : public QGObject
{

    public:
        static QPointer<SessionProxy> wrap( InfcSessionProxy *infObject,
            QObject *parent,
            bool own_gobject = true );

        InfcUserRequest *joinUser( const GParameter *params,
            unsigned int n_params,
            GError **error );

        /**
         * @brief Get the session for this proxy.
         *
         * If your session is not of the type you expected,
         * you probably need to be using a NotePlugin.  See
         * the NotePlugin documentation for more information.
         */
        QPointer<Session> session() const;

    protected:
        SessionProxy( InfcSessionProxy *infProxy,
            QObject *parent = 0,
            bool own_gobject = true );

};

}

#endif

