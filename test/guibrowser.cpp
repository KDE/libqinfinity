#include "guibrowser.h"

#include <QDebug>

#include "guibrowser.moc"

Connection::Connection( QInfinity::QtIo &io,
    const QString &hostname,
    unsigned int port,
    QObject *parent )
    : QObject( parent )
    , hostname( hostname )
    , port( port )
    , io( &io )
    , tcpConnection( 0 )
    , xmppConnection( 0 )
{
}

void Connection::open()
{
    QHostInfo::lookupHost( hostname, this,
        SLOT(slotHostnameLookedUp(QHostInfo)) );
}

void Connection::slotHostnameLookedUp( const QHostInfo &hostInfo )
{
    qDebug() << "Connecting to " << hostInfo.addresses()[0].toString();
    tcpConnection = new QInfinity::TcpConnection( *io,
        QInfinity::IpAddress( hostInfo.addresses()[0] ),
        port,
        this );
    xmppConnection = new QInfinity::XmppConnection( *tcpConnection,
        QInfinity::XmppConnection::Client,
        "localhost", "localhost",
        QInfinity::XmppConnection::PreferTls,
        0, 0, 0,
        this );

    connect( xmppConnection, SIGNAL(statusChanged()),
        this, SLOT(slotXmlConnectionStatusChanged()) );
    connect( xmppConnection, SIGNAL(error( const QString& )),
        this, SLOT(slotXmlConnectionError( const QString& )) );

    tcpConnection->open();
}

void Connection::slotXmlConnectionStatusChanged()
{
    switch( xmppConnection->status() )
    {
        case QInfinity::XmlConnection::Open:
            qDebug() << "Open";
            emit(connected());
            break;
        case QInfinity::XmlConnection::Closed:
            qDebug() << "Closed";
            break;
        case QInfinity::XmlConnection::Opening:
            qDebug() << "Opening";
            break;
    }
}

void Connection::slotXmlConnectionError( const QString &message )
{
    qDebug() << "Error" << message;
}

MyBrowser::MyBrowser()
{
}

void MyBrowser::connectToHost( const QString &hostname,
    unsigned int port )
{
    Connection *connection = new Connection( io, hostname, port, this );
    connect( connection, SIGNAL(connected()), this, SLOT(slotConnectionConnected()) );
    connection->open();
}

void MyBrowser::slotConnectionConnected()
{
    qDebug() << "Connected.";
}

int main( int argc, char **argv )
{
    QInfinity::init();
    QApplication app( argc, argv );
    MyBrowser browser;
    browser.connectToHost( "localhost", 6523 );

    app.exec();
    return 0;
}

