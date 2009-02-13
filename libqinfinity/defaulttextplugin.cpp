#include "defaulttextplugin.h"
#include "textbuffer.h"
#include "textsession.h"
#include "communicationjoinedgroup.h"
#include "xmlconnection.h"

namespace QInfinity
{

DefaultTextPlugin::DefaultTextPlugin()
    : NotePlugin( "InfTexPlugin" )
{
}

Session *DefaultTextPlugin::createSession( CommunicationManager *commMgr,
    CommunicationJoinedGroup *syncGroup,
    XmlConnection *syncConnection )
{

}

}

