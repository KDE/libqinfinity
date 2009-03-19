#include "explorerequest.h"

#include "explorerequest.moc"

namespace QInfinity
{

ExploreRequest::ExploreRequest( InfcExploreRequest *infRequest,
    QObject *parent )
    : Request( INFC_REQUEST( infRequest ), parent )
{
    setupSignals();
}

unsigned int ExploreRequest::nodeId()
{
    return infc_explore_request_get_node_id( INFC_EXPLORE_REQUEST(gobject()) );
}

void ExploreRequest::setupSignals()
{
}

}

