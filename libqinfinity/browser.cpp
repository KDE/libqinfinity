#include "browser.h"

#include <libinfinity/client/infc-browser.h>

namespace QInfinity
{

Browser::Browser( QtIo &io,
    CommunicationManager &comm_manager,
    XmlConnection &connection )
    : QGObject( (GObject*)infc_browser_new( (InfIo*)io.gobject(),
        (InfCommunicationManager*)comm_manager.gobject(),
        (InfXmlConnection*)connection.gobject() ) )
{
}

}

