/*
 * Copyright 2009  Gregory Haynes <greg@greghaynes.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
    : QGObject( other.gobject(), other.parent(), false )
{
}

CommunicationManager::CommunicationManager( InfCommunicationManager *infCommManager,
    QObject *parent,
    bool own_gobject )
    : QGObject( G_OBJECT(infCommManager), parent, own_gobject )
{
}

}

