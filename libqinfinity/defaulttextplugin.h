#ifndef QINFINITY_DEFAULT_TEXT_PLUGIN_H
#define QINFINITY_DEFAULT_TEXT_PLUGIN_H

#include "noteplugin.h"

namespace QInfinity
{

class DefaultTextPlugin
    : public NotePlugin
{

    public:
        DefaultTextPlugin( QObject *parent = 0 );

        Session *createSession( CommunicationManager *commMgr,
            CommunicationJoinedGroup *syncGroup,
            XmlConnection *syncConnection );

};

}

#endif

