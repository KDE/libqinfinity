#include "guibrowser.h"

#include <QDebug>

#include "ui_newconnectionwidget.h"
#include "guibrowser.moc"

NewConnectionDialog::NewConnectionDialog( QWidget *parent )
    : QDialog( parent )
    , ui( new Ui_newConnectionWidget )
{
    ui->setupUi( this );
    connect( ui->okPushButton, SIGNAL(clicked(bool)),
        this, SLOT(slotOkClicked(bool)) );
    connect( ui->cancelPushButton, SIGNAL(clicked(bool)),
        this, SLOT(slotCancelClicked(bool)) );
}

void NewConnectionDialog::slotOkClicked( bool checked )
{
    if( !ui->hostnameLineEdit->text().isEmpty() &&
        !ui->portLineEdit->text().isEmpty() )
    {
        emit(createConnection( ui->hostnameLineEdit->text(),
            ui->portLineEdit->text().toUInt() ));
        deleteLater();
    }
    else
        qDebug() << "invalid input.";
}

void NewConnectionDialog::slotCancelClicked( bool checked )
{
    deleteLater();
}

BrowserMainWindow::BrowserMainWindow( QWidget *parent )
    : QMainWindow( parent )
    , fileModel( new QInfinity::FileModel( this ) )
{
    setupUi();
    setupActions();
}

void BrowserMainWindow::slotNewConnection( bool checked )
{
    NewConnectionDialog *dialog = new NewConnectionDialog( this );
    connect( dialog, SIGNAL(createConnection( const QString&, unsigned int )),
        this, SLOT(slotCreateConnection( const QString&, unsigned int )) );
    dialog->setVisible( true );
}

void BrowserMainWindow::slotCreateConnection( const QString &hostname,
    unsigned int port )
{
    Connection *conn = new Connection( hostname, port, this );
    connect( conn, SIGNAL(connected(Connection*)),
        this, SLOT(slotConnectionConnected(Connection*)) );
    conn->open();
}

void BrowserMainWindow::slotConnectionConnected( Connection *conn )
{
    qDebug() << "Adding " << conn->name();
    fileModel->addConnection( conn->xmppConnection(), conn->name() );
}

void BrowserMainWindow::setupUi()
{
    treeView = new QTreeView( this );
    treeView->setModel( fileModel );
    setCentralWidget( treeView );
    connect( treeView, SIGNAL(expanded(const QModelIndex&)),
        fileModel, SLOT(itemActivated(const QModelIndex&)) );
}

void BrowserMainWindow::setupActions()
{
    newConnectionAction = new QAction( tr("&New Connection..."), this );
    connect( newConnectionAction, SIGNAL(triggered(bool)),
        this, SLOT(slotNewConnection(bool)) );

    QMenu *fileMenu = new QMenu( tr("&File"), this );
    fileMenu->addAction( newConnectionAction );

    menuBar()->addMenu( fileMenu );
}


int main( int argc, char **argv )
{
    QInfinity::init();
    QApplication app( argc, argv );
    BrowserMainWindow mainWindow;
    mainWindow.setVisible( true );

    app.exec();
    QInfinity::deinit();
    return 0;
}

