#ifndef QINFINITY_COMMUNICATION_JOINED_GROUP_H
#define QINFINITY_COMMUNICATION_JOINED_GROUP_H

#include "qgobject.h"

#include <libinfinity/communication/inf-communication-joined-group.h>

#include <QPointer>

namespace QInfinity
{

class CommunicationJoinedGroup
    : public QGObject
{

    public:
        static QPointer<CommunicationJoinedGroup> wrap( InfCommunicationJoinedGroup *infGroup,
            QObject *parent = 0,
            bool own_gobject = true );

    protected:
        CommunicationJoinedGroup( InfCommunicationJoinedGroup *infGroup,
            QObject *parent = 0,
            bool own_gobject = true );

};

}

#endif

