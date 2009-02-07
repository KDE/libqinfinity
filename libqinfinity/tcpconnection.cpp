#include "tcpconnection.h"

#include "tcpconnection.moc"

namespace QInfinity
{

TcpConnection::TcpConnection( QtIo &io,
    const IpAddress &address,
    unsigned int port,
    QObject *parent )
    : QObject( parent )
{
    InfTcpConnection *infObject;

    infObject = INF_TCP_CONNECTION(g_object_new( INF_TYPE_TCP_CONNECTION,
        "io", io.gobject(),
        "remote-address", address.gobject(),
        "remote-port", port,
        NULL ));
    setGobject( G_OBJECT(infObject) );
    setupSignals();
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

TcpConnection::Status TcpConnection::getStatus() const
{
    InfTcpConnectionStatus infStatus;
    Status status;
    InfTcpConnection *connection;

    connection = INF_TCP_CONNECTION(gobject());
    g_object_get( G_OBJECT(connection),
        "status", &status,
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

void TcpConnection::setupSignals()
{
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

