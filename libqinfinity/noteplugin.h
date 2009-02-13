#ifndef QINFINITY_NOTE_PLUGIN_H
#define QINFINITY_NOTE_PLUGIN_H

#include <libinfinity/client/infc-note-plugin.h>

namespace QInfinity
{

class NotePlugin
{

    public:
        NotePlugin();
        virtual ~NotePlugin();

        Session *createSession( CommunicationManager *commMgr,
            CommunicationJoinedGroup *syncGroup,
            XmlConnection *sync_connection );

}

}

#endif

