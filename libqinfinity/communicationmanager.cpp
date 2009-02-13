#include "communicationmanager.h"

#include <libinfinity/communication/inf-communication-manager.h>

namespace QInfinity
{

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

