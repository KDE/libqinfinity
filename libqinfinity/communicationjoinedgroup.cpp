#include "communicationjoinedgroup.h"
#include "wrapperstore.h"

namespace QInfinity
{

QPointer<CommunicationJoinedGroup> CommunicationJoinedGroup::wrap( InfCommunicationJoinedGroup *infObject,
    QObject *parent )
{
    QGObject *wrapptr = WrapperStore::getWrapper( G_OBJECT(infObject) );
    if( wrapptr)
        return dynamic_cast<CommunicationJoinedGroup*>(wrapptr);
    CommunicationJoinedGroup *wrapper = new CommunicationJoinedGroup( infObject, parent );
    WrapperStore::insertWrapper( G_OBJECT(infObject), wrapper );
    return wrapper;
}

CommunicationJoinedGroup::CommunicationJoinedGroup( InfCommunicationJoinedGroup *infGroup,
    QObject *parent,
    bool own_gobject )
    : QGObject( G_OBJECT(infGroup), parent )
{
}

}

