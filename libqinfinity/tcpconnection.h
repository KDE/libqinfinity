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

#ifndef QINFINITY_TCPCONNECTION_H
#define QINFINITY_TCPCONNECTION_H

#include <libinfinity/common/inf-tcp-connection.h>

#include "qgobject.h"
#include "qtio.h"
#include "ipaddress.h"

#include <QObject>
#include <QPointer>

namespace QInfinity
{

class TcpConnection
    : public QGObject
{
    Q_OBJECT;

    public:
        enum Status
        {
            Connecting,
            Connected,
            Closed
        };

        static QPointer<TcpConnection> wrap( InfTcpConnection *infTcpConnection,
            QObject *parent = 0,
            bool own_gobject = true );

        TcpConnection( const IpAddress &ipAddress,
            unsigned int port,
            QObject *parent = 0,
            bool own_gobject = true );
        ~TcpConnection();

        bool open();
        void close();
        Status status() const;
    
    Q_SIGNALS:
        void statusChanged();

    protected:
        TcpConnection( InfTcpConnection *infTcpConnection,
            QObject *parent = 0,
            bool own_gobject = true );
    
    private:
        void setupSignals();

        // Signal callbacks
        void emitStatusChanged();
        static void status_changed_cb( InfTcpConnection *connection,
            const char *property,
            void *user_data );
    
};

}

#endif

