#include "guibrowser.h"

#include "guibrowser.moc"

Connection::Connection( const QString &hostname,
    unsigned int port,
    QObject *parent )
    : QObject( parent )
    , hostname( hostname )
    , port( port )
{
}

void Connection::setup()
{
    QHostInfo::lookupHost( hostname, this,
        SLOT(slotHostnameLookedUp(QHostInfo)) );
}

void Connection::slotHostnameLookedUp( const QHostInfo &hostInfo )
{
    emit(hostnameLookedUp( hostInfo.addresses()[0], port ));
}

MyBrowser::MyBrowser()
{
}

void MyBrowser::connectToHost( const QString &hostname,
    unsigned int port )
{
    Connection *connection = new Connection( hostname, port, this );
    connect( connection, SIGNAL(hostnameLookedUp(const QHostAddress&, unsigned int)),
        this, SLOT(connectToHost(const QHostAddress&, unsigned int)) );
    connection->setup();
}

void MyBrowser::connectToHost( const QHostAddress &address,
    unsigned int port )
{
}

void MyBrowser::slotConnectionStatusChanged()
{
}

int main( int argc, char **argv )
{
    QApplication app( argc, argv );

    app.exec();
    return 0;
}

