#include "guibrowser.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "guibrowser.moc"

NewConnectionDialog::NewConnectionDialog( QWidget *parent )
    : QDialog( parent )
{
    setupUi();
}

NewConnectionDialog::~NewConnectionDialog()
{
    delete nameLineEdit;
    delete hostnameLineEdit;
    delete portLineEdit;
}

void NewConnectionDialog::setupUi()
{
    nameLineEdit = new QLineEdit( this );
    hostnameLineEdit = new QLineEdit( this );
    portLineEdit = new QLineEdit( this );

    QHBoxLayout *nameHorizLayout = new QHBoxLayout();
    nameHorizLayout->addWidget( new QLabel( "Name" ) );
    nameHorizLayout->addWidget( nameLineEdit );

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout( nameHorizLayout );

    setLayout( mainLayout );
}

BrowserMainWindow::BrowserMainWindow( QWidget *parent )
    : QMainWindow( parent )
{
    setupActions();
    setupUi();
}

void BrowserMainWindow::slotNewConnection( bool checked )
{
    NewConnectionDialog *dialog = new NewConnectionDialog( this );
    dialog->setVisible( true );
}

void BrowserMainWindow::setupUi()
{
    menuBar()->addAction( newConnectionAction );
}

void BrowserMainWindow::setupActions()
{
    newConnectionAction = new QAction( "New Connection...", this );
    connect( newConnectionAction, SIGNAL(triggered(bool)),
        this, SLOT(slotNewConnection(bool)) );
}

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

const QString &Connection::hostname() const
{
    return m_hostname;
}

QInfinity::XmppConnection &Connection::xmppConnection() const
{
    return *m_xmppConnection;
}

void Connection::slotHostnameLookedUp( const QHostInfo &hostInfo )
{
    qDebug() << "Connecting to " << hostInfo.addresses()[0].toString();
    tcpConnection = new QInfinity::TcpConnection( QInfinity::IpAddress( hostInfo.addresses()[0] ),
        port,
        this );

    m_xmppConnection = new QInfinity::XmppConnection( *tcpConnection,
        QInfinity::XmppConnection::Client,
        "localhost", "localhost",
        QInfinity::XmppConnection::OnlyTls,
        0, 0, 0,
        this );

    connect( m_xmppConnection, SIGNAL(statusChanged()),
        this, SLOT(slotXmlConnectionStatusChanged()) );

    tcpConnection->open();

}

void Connection::slotXmlConnectionStatusChanged()
{
    switch( m_xmppConnection->status() )
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

void Connection::slotXmlConnectionError( const GError* )
{
    qDebug() << "connection error.";
}

MyBrowser::MyBrowser()
{
    treeView = new QTreeView();
    treeView->setModel( &fileModel );
    treeView->setVisible( true );
    connect( treeView, SIGNAL(expanded( const QModelIndex& )),
        &fileModel, SLOT(itemActivated( const QModelIndex& )) );
}

MyBrowser::~MyBrowser()
{
    delete treeView;
}

void MyBrowser::connectToHost( const QString &hostname,
    unsigned int port )
{
    Connection *connection = new Connection( hostname, port, this );
    connect( connection, SIGNAL(connected()), this, SLOT(slotConnectionConnected()) );
    connection->open();
}

void MyBrowser::slotConnectionConnected()
{
    Connection *connection = dynamic_cast<Connection*>(sender());
    fileModel.addConnection( connection->xmppConnection(), connection->hostname() );
}

int main( int argc, char **argv )
{
    QInfinity::init();
    QApplication app( argc, argv );
    MyBrowser browser;
    browser.connectToHost( "localhost", 6523 );

    app.exec();
    QInfinity::deinit();
    return 0;
}

