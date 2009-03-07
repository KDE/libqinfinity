#include "defaulttextplugin.h"
#include "textdefaultbuffer.h"
#include "textsession.h"
#include "communicationjoinedgroup.h"
#include "xmlconnection.h"

namespace QInfinity
{

DefaultTextPlugin::DefaultTextPlugin( QObject *parent )
    : NotePlugin( "InfText", parent )
{
}

Session *DefaultTextPlugin::createSession( CommunicationManager *commMgr,
    CommunicationJoinedGroup *syncGroup,
    XmlConnection *syncConnection )
{
    TextBuffer *buffer = new TextDefaultBuffer( "utf-8" );
    TextSession *textSession = new TextSession( *commMgr,
        *buffer,
        *syncGroup,
        *syncConnection );
    return textSession;
}

}

