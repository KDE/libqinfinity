#include "communicationmanager.h"

#include <libinfinity/communication/inf-communication-manager.h>

namespace QInfinity
{

CommunicationManager::CommunicationManager( bool own_gobject,
    QObject *parent )
    : QObject( parent )
    , QGObject( G_OBJECT(inf_communication_manager_new()), own_gobject )
{
}

CommunicationManager::CommunicationManager( InfCommunicationManager *infCommManager,
    QObject *parent )
    : QObject( parent )
    , QGObject( G_OBJECT(infCommManager), false )
{
}

CommunicationManager::CommunicationManager( const CommunicationManager &other )
    : QGObject( other.gobject(), false )
{
}

}

