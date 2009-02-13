#include "noteplugin.h"

namespace QInfinity
{

NotePlugin::NotePlugin( QString name )
    : m_name( name )
{
    m_infPlugin.note_type = m_name.toAscii();
    m_infPlugin.session_new = NotePlugin::create_session_cb;
    m_infPlugin.user_data = this;
}

NotePlugin::~NotePlugin()
{
}

InfSession *NotePlugin::create_session_cb( InfIo *io,
    InfCommunicationManager *comm_mgr,
    InfCommunicationJoinedGroup *sync_group,
    InfXmlConnection *sync_connection,
    void *user_data )
{
    NotePlugin *plugin = static_cast<NotePlugin*>(user_data);
}

}

