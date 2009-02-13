#include "communicationjoinedgroup.h"
#include "wrapperstore.h"

namespace QInfinity
{

CommunicationJoinedGroup *CommunicationJoinedGroup::create( InfCommunicationJoinedGroup *infGroup,
    QObject *parent,
    bool own_gobject )
{
    WrapperStore *store = WrapperStore::instance();
    CommunicationJoinedGroup *grp = dynamic_cast<CommunicationJoinedGroup*>(store->findWrapper( G_OBJECT(infGroup) ));
    if( !grp )
        grp = new CommunicationJoinedGroup( infGroup, parent, own_gobject );
    return grp;
}

CommunicationJoinedGroup::CommunicationJoinedGroup( InfCommunicationJoinedGroup *infGroup,
    QObject *parent,
    bool own_gobject )
    : QGObject( G_OBJECT(infGroup), parent )
{
}

}

