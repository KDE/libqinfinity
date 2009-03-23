#ifndef QINFINITY_TEXT_SESSION_H
#define QINFINITY_TEXT_SESSION_H

#include "session.h"
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

class TextSession
    : public Session
{

    public:
        static QPointer<TextSession> wrap( InfTextSession *infSession,
            QObject *parent = 0,
            bool own_gobj = true );

        /**
         * @brief Convenience method for joining a session.
         */
        static InfcUserRequest *joinUser( QPointer<SessionProxy> proxy,
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

