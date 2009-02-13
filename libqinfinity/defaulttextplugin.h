#ifndef QINFINITY_DEFAULT_TEXT_PLUGIN_H
#define QINFINITY_DEFAULT_TEXT_PLUGIN_H

#include "noteplugin.h"

namespace QInfinity
{

class DefaultTextPlugin
    : public NotePlugin
{

    public:
        DefaultTextPlugin();

        Session *createSession( CommunicationManager *commMgr,
            CommunicationJoinedGroup *syncGroup,
            XmlConnection *syncConnection );

};

}

#endif

