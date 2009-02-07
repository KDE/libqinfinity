#include "session.h"

#include <libinfinity/common/inf-session.h>

namespace QInfinity
{

Session::Session( InfSession *infSession,
    QObject *parent )
    : QObject( parent )
    , QGObject( G_OBJECT(infSession), false )
{
}

CommunicationManager Session::communicationManager() const
{
    InfCommunicationManager *commMgr;

    commMgr = inf_session_get_communication_manager( INF_SESSION(gobject()) );
    return CommunicationManager( commMgr );
}

}

