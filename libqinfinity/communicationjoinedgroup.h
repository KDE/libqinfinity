#ifndef QINFINITY_COMMUNICATION_JOINED_GROUP_H
#define QINFINITY_COMMUNICATION_JOINED_GROUP_H

#include "qgobject.h"

#include <libinfinity/communication/inf-communication-joined-group.h>

namespace QInfinity
{

class CommunicationJoinedGroup
    : public QGObject
{

    public:
        static CommunicationJoinedGroup *create( InfCommunicationJoinedGroup *infGroup,
            QObject *parent,
            bool own_gobject = true );

        CommunicationJoinedGroup( InfCommunicationJoinedGroup *infGroup,
            QObject *parent = 0,
            bool own_gobject = false );

};

}

#endif

