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

#ifndef QINFINITY_COMMUNICATION_JOINED_GROUP_H
#define QINFINITY_COMMUNICATION_JOINED_GROUP_H

#include "qgobject.h"

#include <QPointer>

typedef struct _InfCommunicationGroup InfCommunicationGroup;

namespace QInfinity
{

class CommunicationGroup
    : public QGObject
{

    public:
        static QPointer<CommunicationGroup> wrap( InfCommunicationGroup *infGroup,
            QObject *parent = 0,
            bool own_gobject = true );

    protected:
        CommunicationGroup( InfCommunicationGroup *infGroup,
            QObject *parent = 0,
            bool own_gobject = true );

};

}

#endif

