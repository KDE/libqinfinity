#include "xmlconnection.h"

#include "xmlconnection.moc"

namespace QInfinity
{

XmlConnection::XmlConnection( InfXmlConnection *infXmlConnection,
    QObject *parent )
    : QObject( parent )
    , QGObject( G_OBJECT(infXmlConnection) )
{
}

void XmlConnection::close()
{
    InfXmlConnection *infXmlConnection;

    infXmlConnection = INF_XML_CONNECTION(gobject());
    inf_xml_connection_close( infXmlConnection );
}

XmlConnection::Status XmlConnection::getStatus() const
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
        default:
            status = Opening;
    }

    return status;
}

void XmlConnection::registerSignals()
{
    if( !gobject() )
        return;

    g_signal_connect(gobject(), "error", G_CALLBACK(XmlConnection::error_cb), this);
    g_signal_connect(gobject(), "notify::status", G_CALLBACK(XmlConnection::status_changed_cb), this);
}

void XmlConnection::signalError()
{
    emit(error());
}

void XmlConnection::signalStatusChanged()
{
    emit(statusChanged());
}

void XmlConnection::error_cb( const GError *error,
    void *user_data )
{
    static_cast<XmlConnection*>(user_data)->signalError();
}

void XmlConnection::status_changed_cb( InfXmlConnection *infConnection,
    const char *property,
    void *user_data )
{
    static_cast<XmlConnection*>(user_data)->signalError();
}

}

