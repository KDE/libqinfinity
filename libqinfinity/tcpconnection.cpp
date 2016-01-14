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

#include "tcpconnection.h"
#include "wrapperstore.h"



namespace QInfinity
{

QPointer<TcpConnection> TcpConnection::wrap( InfTcpConnection *infTcpConnection,
    QObject *parent,
    bool own_gobject )
{
    QGObject *wrapptr = WrapperStore::getWrapper( G_OBJECT(infTcpConnection), own_gobject );
    if( wrapptr)
        return dynamic_cast<TcpConnection*>(wrapptr);
    TcpConnection *connection = new TcpConnection( infTcpConnection, parent, own_gobject );
    return connection;
}

TcpConnection::TcpConnection( const IpAddress &address,
    unsigned int port,
    QObject *parent,
    bool own_gobject )
    : QGObject( parent )
{
    InfTcpConnection *infObject;

    infObject = INF_TCP_CONNECTION(g_object_new( INF_TYPE_TCP_CONNECTION,
        "io", QtIo::instance()->gobject(),
        "remote-address", address.gobject(),
        "remote-port", port,
        NULL ));
    setGobject( G_OBJECT(infObject), true );
    setupSignals();
}

TcpConnection::~TcpConnection()
{
    if( status() != Closed )
        close();
}

bool TcpConnection::open()
{
    InfTcpConnection *connection;

    connection = INF_TCP_CONNECTION(gobject());
    return inf_tcp_connection_open(connection, 0) == 0;
}

void TcpConnection::close()
{
    InfTcpConnection *connection;

    connection = INF_TCP_CONNECTION(gobject());
    inf_tcp_connection_close(connection);
}

TcpConnection::Status TcpConnection::status() const
{
    static InfTcpConnectionStatus infStatus;
    static Status status;

    g_object_get( gobject(),
        "status", &infStatus,
           NULL );

    switch( infStatus )
    {
        case INF_TCP_CONNECTION_CONNECTING:
            status = Connecting;
            break;
        case INF_TCP_CONNECTION_CONNECTED:
            status = Connected;
            break;
        case INF_TCP_CONNECTION_CLOSED:
            status = Closed;
    }

    return status;
}

TcpConnection::TcpConnection( InfTcpConnection *infTcpConnection,
    QObject *parent,
    bool own_gobject )
    : QGObject( G_OBJECT(infTcpConnection), parent, own_gobject )
{
}

void TcpConnection::setupSignals()
{
    if( !gobject() )
        return;

    InfTcpConnection *connection;

    connection = INF_TCP_CONNECTION(gobject());
    g_signal_connect( G_OBJECT(connection),
        "notify::status",
        G_CALLBACK(TcpConnection::status_changed_cb),
        this );

}

void TcpConnection::emitStatusChanged()
{
    emit(statusChanged());
}

void TcpConnection::status_changed_cb( InfTcpConnection *connection,
    const char *property,
    void *user_data )
{
    static_cast<TcpConnection*>(user_data)->emitStatusChanged();
}

}

