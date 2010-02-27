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

#include "noteplugin.h"
#include "communicationmanager.h"
#include "communicationjoinedgroup.h"
#include "xmlconnection.h"

#include <QChar>
#include <QDebug>

namespace QInfinity
{

NotePlugin::NotePlugin( QString name, QObject *parent )
    : QObject( parent )
{
    m_name = new char[name.size()+1];
    strcpy(m_name, name.toAscii());
    m_infPlugin.note_type = m_name;
    m_infPlugin.session_new = NotePlugin::create_session_cb;
    m_infPlugin.user_data = this;
}

NotePlugin::~NotePlugin()
{
    delete m_name;
}

InfSession *NotePlugin::create_session_cb( InfIo *io,
    InfCommunicationManager *comm_mgr,
    InfSessionStatus status,
    InfCommunicationJoinedGroup *sync_group,
    InfXmlConnection *sync_connection,
    void *user_data )
{
    NotePlugin *plugin = static_cast<NotePlugin*>(user_data);
    CommunicationManager *commMgr = CommunicationManager::wrap( comm_mgr, plugin );
    Session::Status cpp_status = Session::infStatusToCpp(status);
    CommunicationJoinedGroup *joinedGroup = CommunicationJoinedGroup::wrap( sync_group, plugin );
    XmlConnection *connection = XmlConnection::wrap( sync_connection, plugin );
    Session *session =  plugin->createSession( commMgr, cpp_status, joinedGroup, connection );
    return INF_SESSION(session->gobject());
}

InfcNotePlugin *NotePlugin::infPlugin()
{
    return &m_infPlugin;
}

}

