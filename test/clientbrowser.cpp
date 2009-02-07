#include "clientbrowser.h"

#include "clientbrowser.moc"

MyBrowser::MyBrowser( QInfinity::QtIo &io )
    : m_io( &io )
    , connection( new QInfinity::TcpConnection( io, QInfinity::IpAddress( "127.0.0.1" ), 6523 ) )
    , xmppConnection( new QInfinity::XmppConnection( *connection,
        QInfinity::XmppConnection::Client,
        "localhost",
        "localhost",
        QInfinity::XmppConnection::PreferTls,
        0,
        0,
        0,
        this ) )
{
    setupSignals();
    connection->open();
    std::cout << "running\n";
    fflush(stdout);
}

MyBrowser::~MyBrowser()
{
    delete xmppConnection;
    delete connection;
}

void MyBrowser::statusChanged()
{
    std::cout << "Status changed\n";
    QInfinity::TcpConnection::Status status;
    status = connection->getStatus();
    switch( status )
    {
        case QInfinity::TcpConnection::Connecting:
            std::cout << "Connecting\n";
            break;
        case QInfinity::TcpConnection::Connected:
            std::cout << "Connected\n";
            break;
        case QInfinity::TcpConnection::Closed:
            std::cout << "Closed\n";
    }

    fflush(stdout);
}

void MyBrowser::setupSignals()
{
    connect( connection, SIGNAL(statusChanged()),
        this, SLOT(statusChanged()) );
}

int main( int argc, char **argv )
{
    QApplication app( argc, argv );

    QInfinity::init();
    QInfinity::QtIo io;
    MyBrowser browser( io );

    return app.exec();
    QInfinity::deinit();
}

