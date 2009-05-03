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

#ifndef QINFINITY_COMMUNICATION_MANAGER_H
#define QINFINITY_COMMUNICATION_MANAGER_H

#include "qgobject.h"

#include <QObject>
#include <QPointer>

typedef struct _InfCommunicationManager InfCommunicationManager;

namespace QInfinity
{

/**
 * @brief Manages multiple communication sessions.
 */
class CommunicationManager
    : public QGObject
{

    public:
        /**
         * @brief Create manager making use of object store.
         */
        static QPointer<CommunicationManager> wrap( InfCommunicationManager *infCommManager,
            QObject *parent = 0,
            bool own_gobject = true );

        CommunicationManager( QObject *parent = 0, bool own_gobject = true );
        CommunicationManager( const CommunicationManager &other );

    protected:
        /**
         * @brief Create a new Communication Manager.
         * @param own_gobject Take ownership of the created GObject.
         *
         * The own_gobject parameter specifies if the created GObject will be
         * deleted when the CommunicationManager is deleted.  If you dont want
         * to store this CommunicationManager, you can set this to false.
         */
        CommunicationManager( InfCommunicationManager *infCommManager,
            QObject *parent = 0,
            bool own_gobject = true );

};

}

#endif

