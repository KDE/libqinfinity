#include "guibrowser.h"
#include "createitemdialog.h"

#include <QMessageBox>
#include <QStatusBar>
#include <QDebug>
#include <QApplication>
#include <QItemSelectionModel>

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
    , fileModel( new QInfinity::BrowserModel( this ) )
{
    setupActions();
    setupUi();
}

void BrowserMainWindow::slotNewConnection()
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
    connect( conn, SIGNAL(connecting(Connection*)),
        this, SLOT(slotConnectionConnecting(Connection*)) );
    connect( conn, SIGNAL(disconnecting(Connection*)),
        this, SLOT(slotConnectionDisconnecting(Connection*)) );
    connect( conn, SIGNAL(connected(Connection*)),
        this, SLOT(slotConnectionConnected(Connection*)) );
    connect( conn, SIGNAL(error(Connection*, QString)),
        this, SLOT(slotConnectionError(Connection*, QString)) );
    connect( conn, SIGNAL(disconnected(Connection*)),
        this, SLOT(slotConnectionDisconnected(Connection*)) );
    conn->open();
}

void BrowserMainWindow::slotConnectionConnecting( Connection *conn )
{
    QString msg = "Connecting to " + conn->name() + ".";
    statusLabel->setText( msg );
}

void BrowserMainWindow::slotConnectionDisconnecting( Connection *conn )
{
    QString msg = "Disconnecting from " + conn->name() + ".";
    statusLabel->setText( msg );
}

void BrowserMainWindow::slotConnectionConnected( Connection *conn )
{
    qDebug() << "Adding " << conn->name();
    statusLabel->setText( "Connected." );
    fileModel->addConnection( conn->xmppConnection(), conn->name() );
}

void BrowserMainWindow::slotConnectionDisconnected( Connection *conn )
{
    statusLabel->setText( "Disconnected." );
}

void BrowserMainWindow::slotConnectionError( Connection *conn,
    QString message )
{
    QString full_msg = "Error with connection ";
    full_msg += conn->name();
    full_msg += ": ";
    full_msg += message;
    QMessageBox::critical( this, "Connection error", full_msg );
}

void BrowserMainWindow::slotSelectionChanged( const QItemSelection &selected,
    const QItemSelection &deselected )
{
    Q_UNUSED(deselected)
    newConnectionAction->setEnabled( canCreateConnection( selected ) );
    newFolderAction->setEnabled( canCreateFolder( selected ) );
    newNoteAction->setEnabled( canCreateNote( selected ) );
    deleteAction->setEnabled( canDeleteItem( selected ) );
}

void BrowserMainWindow::slotQuit()
{
    exit(0);
}

void BrowserMainWindow::slotCreateFolder()
{
    CreateItemDialog *dialog = new CreateItemDialog( "Create folder named: ",
        this );
    dialog->exec();
    delete dialog;
}

void BrowserMainWindow::contextMenuEvent( QContextMenuEvent *event )
{
    if( !event )
        return;

    showContextMenu( event->globalPos() );
}

void BrowserMainWindow::setupUi()
{
    treeView = new QTreeView( this );
    treeView->setModel( fileModel );
    connect( treeView, SIGNAL(expanded(const QModelIndex&)),
        fileModel, SLOT(itemActivated(const QModelIndex&)) );
    connect( treeView->selectionModel(), SIGNAL(
            selectionChanged(const QItemSelection&, const QItemSelection&)),
        this, SLOT(slotSelectionChanged(
            const QItemSelection&, const QItemSelection&)) );
    setStatusBar( new QStatusBar( this ) );
    statusLabel = new QLabel();
    statusBar()->addWidget( statusLabel );
    setCentralWidget( treeView );
}

void BrowserMainWindow::setupActions()
{
    quitAction = new QAction( tr("&Quit"), this );
    newConnectionAction = new QAction( tr("&New Connection..."), this );
    newFolderAction = new QAction( tr("Create &Folder..."), this );
    newFolderAction->setEnabled( false );
    newNoteAction = new QAction( tr("Create &Note..."), this );
    newNoteAction->setEnabled( false );
    deleteAction = new QAction( tr("Delete"), this );
    deleteAction->setEnabled( false );

    connect( quitAction, SIGNAL(triggered(bool)),
        this, SLOT(slotQuit()) );
    connect( newConnectionAction, SIGNAL(triggered(bool)),
        this, SLOT(slotNewConnection()) );
    connect( newFolderAction, SIGNAL(triggered(bool)),
        this, SLOT(slotCreateFolder()) );

    QMenu *fileMenu = new QMenu( tr("&File"), this );
    fileMenu->addAction( newConnectionAction );
    fileMenu->addAction( quitAction );

    menuBar()->addMenu( fileMenu );
}

void BrowserMainWindow::showContextMenu( const QPoint &globalPos )
{
    static QMenu *contextMenu = 0;
    if( !contextMenu )
    {
        contextMenu = new QMenu( this );
        contextMenu->addAction( newConnectionAction );
        contextMenu->addAction( newFolderAction );
        contextMenu->addAction( newNoteAction );
        contextMenu->addAction( deleteAction );

    }
    contextMenu->popup( globalPos );
}

bool BrowserMainWindow::canCreateConnection( const QItemSelection &selected )
{
    return true;
}

bool BrowserMainWindow::canCreateFolder( const QItemSelection &selected )
{
    QList<QModelIndex> indexes = selected.indexes();
    if( indexes.size() != 1 )
        return false;
    QStandardItem *item = fileModel->itemFromIndex( indexes[0] );
    if( item->type() != QInfinity::BrowserItemFactory::NodeItem )
        return false;
    return dynamic_cast<QInfinity::NodeItem*>(item)->isDirectory();
}

bool BrowserMainWindow::canCreateNote( const QItemSelection &selected )
{
    return false;
}

bool BrowserMainWindow::canDeleteItem( const QItemSelection &selected )
{
    return false;
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

