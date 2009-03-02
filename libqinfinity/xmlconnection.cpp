#include "xmlconnection.h"
#include "tcpconnection.h"
#include "wrapperstore.h"

#include <QDebug>

#include "xmlconnection.moc"

namespace QInfinity
{

XmlConnection *XmlConnection::create( InfXmlConnection *infXmlConnection,
    QObject *parent,
    bool own_gobject )
{
    WrapperStore *store = WrapperStore::instance();
    XmlConnection *connection = dynamic_cast<XmlConnection*>(store->findWrapper( G_OBJECT(infXmlConnection) ));
    if( !connection )
        connection = new XmlConnection( infXmlConnection, parent );
    return connection;
}

XmlConnection::XmlConnection( InfXmlConnection *infXmlConnection,
    QObject *parent,
    bool own_gobject )
    : QGObject( G_OBJECT(infXmlConnection), own_gobject, parent )
{
    registerSignals();
}

XmlConnection::~XmlConnection()
{
    if( status() == Open )
        close();
}

TcpConnection *XmlConnection::tcpConnection()
{
    InfTcpConnection *infTcpConnection;

    g_object_get( gobject(),
        "tcp-connection", &infTcpConnection,
        NULL );

    return dynamic_cast<TcpConnection*>(WrapperStore::instance()->findWrapper( G_OBJECT(infTcpConnection) ));
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

void XmlConnection::registerSignals()
{
    g_signal_connect(gobject(), "error", G_CALLBACK(XmlConnection::error_cb), this);
    g_signal_connect(gobject(), "notify::status", G_CALLBACK(XmlConnection::status_changed_cb), this);
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

