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

#include "xmlconnection.h"
#include "tcpconnection.h"
#include "wrapperstore.h"

#include <QDebug>



namespace QInfinity
{

QPointer<XmlConnection> XmlConnection::wrap( InfXmlConnection *infXmlConnection,
    QObject *parent,
    bool own_gobject )
{
    QGObject *wrapptr = WrapperStore::getWrapper( G_OBJECT(infXmlConnection), own_gobject );
    if( wrapptr)
        return dynamic_cast<XmlConnection*>(wrapptr);
    XmlConnection *connection = new XmlConnection( infXmlConnection, parent, own_gobject );
    return connection;
}

XmlConnection::~XmlConnection()
{
    if( status() == Open )
        close();
    g_signal_handler_disconnect( gobject(),
        error_handler );
    g_signal_handler_disconnect( gobject(),
        status_handler );
}

QPointer<TcpConnection> XmlConnection::tcpConnection()
{
    InfTcpConnection *infTcpConnection;

    g_object_get( gobject(),
        "tcp-connection", &infTcpConnection,
        NULL );

    return TcpConnection::wrap( infTcpConnection );
}

void XmlConnection::close()
{
    InfXmlConnection *infXmlConnection;

    infXmlConnection = INF_XML_CONNECTION(gobject());
    inf_xml_connection_close( infXmlConnection );
}

XmlConnection::Status XmlConnection::status() const
{
    InfXmlConnectionStatus infStatus;
    Status status;
    InfXmlConnection *connection;

    connection = INF_XML_CONNECTION(gobject());
    g_object_get( G_OBJECT(connection),
        "status", &infStatus,
           NULL );

    switch( infStatus )
    {
        case INF_XML_CONNECTION_CLOSED:
            status = Closed;
            break;
        case INF_XML_CONNECTION_CLOSING:
            status = Closing;
            break;
        case INF_XML_CONNECTION_OPEN:
            status = Open;
            break;
        case INF_XML_CONNECTION_OPENING:
            status = Opening;
            break;
        default:
            status = Closed;
    }

    return status;
}

XmlConnection::XmlConnection( InfXmlConnection *infXmlConnection,
    QObject *parent,
    bool own_gobject )
    : QGObject( G_OBJECT(infXmlConnection), parent, own_gobject )
{
    if ( INF_IS_SIMULATED_CONNECTION(infXmlConnection) ) {
        inf_simulated_connection_set_mode(INF_SIMULATED_CONNECTION(infXmlConnection), INF_SIMULATED_CONNECTION_IMMEDIATE);
    }
    registerSignals();
}

void XmlConnection::registerSignals()
{
    error_handler = g_signal_connect(gobject(), "error", G_CALLBACK(XmlConnection::error_cb), this);
    status_handler = g_signal_connect(gobject(), "notify::status", G_CALLBACK(XmlConnection::status_changed_cb), this);
}

void XmlConnection::signalError( const GError *err )
{
    emit(error( err ));
}

void XmlConnection::signalStatusChanged()
{
    emit(statusChanged());
}

void XmlConnection::error_cb( InfXmlConnection *infConnection,
    const GError *error,
    void *user_data )
{
    static_cast<XmlConnection*>(user_data)->signalError( error );
}

void XmlConnection::status_changed_cb( InfXmlConnection *infConnection,
    const char *property,
    void *user_data )
{
    static_cast<XmlConnection*>(user_data)->signalStatusChanged();
}

}

