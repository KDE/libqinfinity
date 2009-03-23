#include "communicationjoinedgroup.h"
#include "wrapperstore.h"

namespace QInfinity
{

QPointer<CommunicationJoinedGroup> CommunicationJoinedGroup::wrap( InfCommunicationJoinedGroup *infObject,
    QObject *parent,
    bool own_gobject )
{
    QGObject *wrapptr = WrapperStore::getWrapper( G_OBJECT(infObject), own_gobject );
    if( wrapptr)
        return dynamic_cast<CommunicationJoinedGroup*>(wrapptr);
    CommunicationJoinedGroup *wrapper = new CommunicationJoinedGroup( infObject, parent, own_gobject );
    return wrapper;
}

CommunicationJoinedGroup::CommunicationJoinedGroup( InfCommunicationJoinedGroup *infGroup,
    QObject *parent,
    bool own_gobject )
    : QGObject( G_OBJECT(infGroup), parent, own_gobject )
{
}

}

