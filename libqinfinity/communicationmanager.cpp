#include "communicationmanager.h"
#include "wrapperstore.h"

#include <libinfinity/communication/inf-communication-manager.h>

namespace QInfinity
{

CommunicationManager *CommunicationManager::create( QObject *parent,
    bool own_gobject )
{
    WrapperStore *store = WrapperStore::instance();
    CommunicationManager *mgr = new CommunicationManager( parent, own_gobject );
    store->storeWrapper( mgr->gobject(), mgr, true );
}

CommunicationManager *CommunicationManager::create( InfCommunicationManager *inf_mgr,
    QObject *parent,
    bool own_gobject )
{
    WrapperStore *store = WrapperStore::instance();
    CommunicationManager *mgr = dynamic_cast<CommunicationManager*>(store->findWrapper( G_OBJECT(inf_mgr) ));
    if( !mgr )
        mgr = new CommunicationManager( inf_mgr, parent );
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

