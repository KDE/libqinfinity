#include "connection.h"

#include "connection.moc"

Connection::Connection( const QString &hostname,
    unsigned int port,
    QObject *parent )
    : QObject( parent )
    , m_hostname( hostname )
    , port( port )
    , tcpConnection( 0 )
    , m_xmppConnection( 0 )
{
}

Connection::~Connection()
{
    delete tcpConnection;
    delete m_xmppConnection;
}

void Connection::open()
{
    QHostInfo::lookupHost( hostname(), this,
        SLOT(slotHostnameLookedUp(QHostInfo)) );
}

QString Connection::hostname() const
{
    return m_hostname;
}

QInfinity::XmppConnection &Connection::xmppConnection() const
{
    return *m_xmppConnection;
}

QString Connection::name() const
{
    QString ret = m_hostname;
    ret += ":";
    ret += QString::number( port );
    return ret;
}

void Connection::slotHostnameLookedUp( const QHostInfo &hostInfo )
{
    if( hostInfo.addresses().size() == 0 )
    {
        qDebug() << "Couldnt find hostname.";
        return;
    }
    qDebug() << "Connecting to " << hostInfo.addresses()[0].toString();
    tcpConnection = new QInfinity::TcpConnection( QInfinity::IpAddress( hostInfo.addresses()[0] ),
        port,
        this );

    m_xmppConnection = new QInfinity::XmppConnection( *tcpConnection,
        QInfinity::XmppConnection::Client,
        "localhost", "localhost",
        QInfinity::XmppConnection::PreferTls,
        0, 0, 0,
        this );

    connect( m_xmppConnection, SIGNAL(statusChanged()),
        this, SLOT(slotXmlConnectionStatusChanged()) );
    connect( m_xmppConnection, SIGNAL(error(const GError*)),
        this, SLOT(slotXmlConnectionError(const GError*)) );

    tcpConnection->open();

}

void Connection::slotXmlConnectionStatusChanged()
{
    switch( m_xmppConnection->status() )
    {
        case QInfinity::XmlConnection::Open:
            qDebug() << "Open";
            emit(connected( this ));
            break;
        case QInfinity::XmlConnection::Closed:
            qDebug() << "Closed";
            break;
        case QInfinity::XmlConnection::Opening:
            qDebug() << "Opening";
            break;
    }
}

void Connection::slotXmlConnectionError( const GError *err )
{
    qDebug() << "connection error: " << err->message;
    emit(error());
}

