#include "noteplugin.h"
#include "communicationmanager.h"
#include "communicationjoinedgroup.h"
#include "xmlconnection.h"
#include "session.h"

#include <QChar>
#include <QDebug>

namespace QInfinity
{

NotePlugin::NotePlugin( QString name, QObject *parent )
    : QObject( parent )
{
    m_name = new char(name.size()+1);
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
    InfCommunicationJoinedGroup *sync_group,
    InfXmlConnection *sync_connection,
    void *user_data )
{
    NotePlugin *plugin = static_cast<NotePlugin*>(user_data);
    CommunicationManager *commMgr = CommunicationManager::create( comm_mgr );
    CommunicationJoinedGroup *joinedGroup = CommunicationJoinedGroup::create( sync_group );
    XmlConnection *connection = XmlConnection::create( sync_connection );
    Session *session =  plugin->createSession( commMgr, joinedGroup, connection );
    return INF_SESSION(session->gobject());
}

InfcNotePlugin *NotePlugin::infPlugin()
{
    return &m_infPlugin;
}

}

