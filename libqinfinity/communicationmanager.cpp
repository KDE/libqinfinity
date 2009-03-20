#include "communicationmanager.h"
#include "wrapperstore.h"

#include <libinfinity/communication/inf-communication-manager.h>

namespace QInfinity
{

QPointer<CommunicationManager> CommunicationManager::wrap( InfCommunicationManager *infCommManager,
    QObject *parent )
{
    QGObject *wrapptr = WrapperStore::getWrapper( G_OBJECT(infCommManager) );
    if( wrapptr)
        return dynamic_cast<CommunicationManager*>(wrapptr);
    CommunicationManager *mgr = new CommunicationManager( infCommManager, parent );
    WrapperStore::insertWrapper( G_OBJECT(infCommManager), mgr );
    return mgr;
}

CommunicationManager::CommunicationManager( QObject *parent,
    bool own_gobject )
    : QGObject( G_OBJECT(inf_communication_manager_new()),
        own_gobject,
        parent )
{
}

CommunicationManager::CommunicationManager( InfCommunicationManager *infCommManager,
    QObject *parent )
    : QGObject( G_OBJECT(infCommManager), false, parent )
{
}

CommunicationManager::CommunicationManager( const CommunicationManager &other )
    : QGObject( other.gobject(), false )
{
}

}

