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

#ifndef QINFINITY_TEXT_SESSION_H
#define QINFINITY_TEXT_SESSION_H

#include "adoptedsession.h"
#include "sessionproxy.h"
#include "user.h"

#include <libinfinity/client/infc-user-request.h>
#include <libinftext/inf-text-session.h>

#include <QPointer>

namespace QInfinity
{

class CommunicationManager;
class TextBuffer;
class CommunicationJoinedGroup;
class XmlConnection;
class UserRequest;

class TextSession
    : public AdoptedSession
{

    public:
        static QPointer<TextSession> wrap( InfTextSession *infSession,
            QObject *parent = 0,
            bool own_gobj = true );

        /**
         * @brief Convenience method for joining a session.
         */
        static UserRequest *joinUser( QPointer<SessionProxy> proxy,
            const QString &name,
            double hue,
            unsigned int caretPosition = 0,
            User::Status userStatus = User::Active );
    
        TextSession( CommunicationManager &commMgr,
            TextBuffer &textBuffer,
            CommunicationJoinedGroup &commGroup,
            XmlConnection &connection );

        Session::Type type() const;
        QPointer<Buffer> buffer() const;

    protected:
        TextSession( InfTextSession *infSession,
            QObject *parent = 0,
            bool own_gobj = true );

};

}

#endif

