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

#include "defaulttextplugin.h"
#include "textdefaultbuffer.h"
#include "textsession.h"
#include "communicationjoinedgroup.h"
#include "xmlconnection.h"

namespace QInfinity
{

DefaultTextPlugin::DefaultTextPlugin( QObject *parent )
    : NotePlugin( "InfText", parent )
{
}

Session *DefaultTextPlugin::createSession( CommunicationManager *commMgr,
    CommunicationJoinedGroup *syncGroup,
    XmlConnection *syncConnection )
{
    TextBuffer *buffer = new TextDefaultBuffer( "UTF-8" );
    TextSession *textSession = new TextSession( *commMgr,
        *buffer,
        *syncGroup,
        *syncConnection );
    return textSession;
}

}

