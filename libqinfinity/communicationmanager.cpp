#include "communicationmanager.h"
#include "wrapperstore.h"

#include <libinfinity/communication/inf-communication-manager.h>

namespace QInfinity
{

QPointer<CommunicationManager> CommunicationManager::wrap( InfCommunicationManager *infCommManager,
    QObject *parent,
    bool own_gobject )
{
    QGObject *wrapptr = WrapperStore::getWrapper( G_OBJECT(infCommManager), own_gobject );
    if( wrapptr)
        return dynamic_cast<CommunicationManager*>(wrapptr);
    CommunicationManager *mgr = new CommunicationManager( infCommManager, parent, own_gobject );
    return mgr;
}

CommunicationManager::CommunicationManager( QObject *parent,
    bool own_gobject )
    : QGObject( G_OBJECT(inf_communication_manager_new()),
        parent,
        own_gobject )
{
}

CommunicationManager::CommunicationManager( const CommunicationManager &other )
    : QGObject( other.gobject(), false )
{
}

CommunicationManager::CommunicationManager( InfCommunicationManager *infCommManager,
    QObject *parent,
    bool own_gobject )
    : QGObject( G_OBJECT(infCommManager), parent, own_gobject )
{
}

}

