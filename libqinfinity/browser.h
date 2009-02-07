#ifndef QINFINITY_BROWSER_H
#define QINFINITY_BROWSER_H

#include "qgobject.h"
#include "xmlconnection.h"
#include "qtio.h"
#include "communicationmanager.h"

namespace QInfinity
{

class Browser
    : QGObject
{

    public:
        Browser( QtIo &io,
            CommunicationManager &comm_manager,
            XmlConnection &connection );

};

}

#endif

