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

#ifndef QINFINITY_QTIOWATCH_H
#define QINFINITY_QTIOWATCH_H

#include <libinfinity/common/inf-io.h>

#include <QSocketNotifier>
#include <QObject>

class QSocketNotifier;

namespace QInfinity
{

/**
 * @brief Handles creation of all notifiers for a given socket.
 */
class QtIoWatch
    : public QObject
{
    Q_OBJECT

    public:
        QtIoWatch( int socket,
            InfIoEvent events,
            InfIoWatchFunc handler,
            void *user_data,
            GDestroyNotify destroy_notify,
               QObject *parent = 0 );
        ~QtIoWatch();

        void setEvents( InfIoEvent events );
        void setIncomingEvent( bool enable );
        void setOutgoingEvent( bool enable );
        void setErrorEvent( bool enable );
    
    private Q_SLOTS:
        void incomingActivated( int socket );
        void outgoingActivated( int socket );
        void errorActivated( int socket );

    private:

        int m_socket;
        InfIoWatchFunc m_handler;
        void *m_user_data;
        GDestroyNotify m_destroy_notify;

        /* Because there are so few event types, we may as
         * well hard code pointers for efficiency's sake. */
        QSocketNotifier *m_incomingNotifier;
        QSocketNotifier *m_outgoingNotifier;
        QSocketNotifier *m_errorNotifier;

};

}

#endif

