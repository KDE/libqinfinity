/*
 * Copyright 2009  Gregory Haynes <greg@greghaynes.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

