#ifndef QINFINITY_TEXT_SESSION_H
#define QINFINITY_TEXT_SESSION_H

#include "session.h"

#include <libinftext/inf-text-session.h>

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
        static TextSession *create( InfTextSession *infSession,
            QObject *parent = 0 );
    
        TextSession( CommunicationManager &commMgr,
            TextBuffer &textBuffer,
            CommunicationJoinedGroup &commGroup,
            XmlConnection &connection );

        Session::Type type() const;
        Buffer *buffer() const;

    protected:
        TextSession( InfTextSession *infSession,
            QObject *parent = 0 );

};

}

#endif

