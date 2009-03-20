#ifndef QINFINITY_TEXT_SESSION_H
#define QINFINITY_TEXT_SESSION_H

#include "session.h"

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
            bool own_gobj = false );
    
        TextSession( CommunicationManager &commMgr,
            TextBuffer &textBuffer,
            CommunicationJoinedGroup &commGroup,
            XmlConnection &connection );

        Session::Type type() const;
        Buffer *buffer() const;

    protected:
        TextSession( InfTextSession *infSession,
            QObject *parent = 0,
            bool own_gobj = false );

};

}

#endif

