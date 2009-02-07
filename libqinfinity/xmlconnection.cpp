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

