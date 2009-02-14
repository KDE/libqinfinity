#include "shellbrowser.h"

#include "shellbrowser.moc"

MyBrowser::MyBrowser()
    : connection( new QInfinity::TcpConnection( QInfinity::IpAddress( "127.0.0.1" ), 6523 ) )
    , xmppConnection( new QInfinity::XmppConnection( *connection,
        QInfinity::XmppConnection::Client,
        "localhost",
        "localhost",
        QInfinity::XmppConnection::PreferTls,
        0,
        0,
        0,
        this ) )
    , commMgr( new QInfinity::CommunicationManager() )
    , browser( 0 )
{
    setupSignals();
    connection->open();
    std::cout << "running\n";
    fflush(stdout);
}

MyBrowser::~MyBrowser()
{
    if( browser )
        delete browser;
    delete xmppConnection;
    delete connection;
    delete commMgr;
}

void MyBrowser::statusChanged()
{
    std::cout << "Status changed\n";
    QInfinity::TcpConnection::Status status;
    status = connection->status();
    switch( status )
    {
        case QInfinity::TcpConnection::Connecting:
            std::cout << "Connecting\n";
            break;
        case QInfinity::TcpConnection::Connected:
            std::cout << "Connected\n";
            browser = new QInfinity::Browser( *commMgr, *xmppConnection );
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

void notify_status_cb(InfTcpConnection *conn, const char *prop )
{
    qDebug() << "status";
}

void error_cb(InfXmppConnection *conn, GError *err, void *user_data)
{
    qDebug() << "err" << user_data;
}

int main( int argc, char **argv )
{
    QApplication app( argc, argv );

    QInfinity::init();

    QInfinity::QtIo *io = QInfinity::QtIo::instance();
    InfIpAddress *addr = inf_ip_address_new_from_string( "127.0.0.1" );
    InfTcpConnection *connection;
    InfXmppConnection *xmpp;

    connection = INF_TCP_CONNECTION(g_object_new(
        INF_TYPE_TCP_CONNECTION,
        "io", INF_IO(io->gobject()),
        "remote-address", addr,
        "remote-port", 6523,
        NULL
    ));

    inf_ip_address_free(addr);

    xmpp = INF_XMPP_CONNECTION(inf_xmpp_connection_new(
        connection,
        INF_XMPP_CONNECTION_CLIENT,
        NULL,
        "jabber.0x539.de",
        INF_XMPP_CONNECTION_SECURITY_ONLY_TLS,
        NULL,
        NULL,
        NULL
    ));

    g_signal_connect(G_OBJECT(xmpp), "error", G_CALLBACK(error_cb), (void*)1);
    g_signal_connect(G_OBJECT(xmpp), "notify::status", G_CALLBACK(notify_status_cb), 0);

    inf_tcp_connection_open( connection, 0 );
    
    app.exec();
    QInfinity::deinit();
    return 0;
}

