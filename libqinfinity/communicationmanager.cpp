#include "communicationmanager.h"

#include <libinfinity/communication/inf-communication-manager.h>

namespace QInfinity
{

CommunicationManager::CommunicationManager()
    : QGObject( (GObject*)inf_communication_manager_new() )
{
}

}

