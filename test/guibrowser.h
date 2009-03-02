#ifndef QINFINITY_TEST_GUIBROWSER_H
#define QINFINITY_TEST_GUIBROWSER_H

#include "init.h"
#include "qtio.h"
#include "ipaddress.h"
#include "tcpconnection.h"
#include "xmppconnection.h"
#include "browsermodel.h"
#include "browseritemfactory.h"

#include "connection.h"

#include <QApplication>
#include <QObject>
#include <QList>
#include <QTreeView>
#include <QHostInfo>
#include <QHostAddress>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QLabel>
#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QContextMenuEvent>

#include <glib/gerror.h>

class Ui_newConnectionWidget;

class NewConnectionDialog
    : public QDialog
{
    Q_OBJECT

    public:
        NewConnectionDialog( QWidget *parent = 0 );

    Q_SIGNALS:
        void createConnection( const QString &hostname,
            unsigned int port );

    private Q_SLOTS:
        void slotOkClicked( bool );
        void slotCancelClicked( bool );

    private:
        Ui_newConnectionWidget *ui;
};

class BrowserMainWindow
    : public QMainWindow
{
    Q_OBJECT

    public:
        BrowserMainWindow( QWidget *parent = 0 );

    private Q_SLOTS:
        void slotNewConnection();
        void slotCreateConnection( const QString &hostname,
            unsigned int port );
        void slotConnectionConnecting( Connection *conn );
        void slotConnectionDisconnecting( Connection *conn );
        void slotConnectionConnected( Connection *conn );
        void slotConnectionDisconnected( Connection *conn );
        void slotConnectionError( Connection *conn, QString message );
        void slotSelectionChanged( const QItemSelection &selected,
            const QItemSelection &deselected );
        void slotQuit();
        void slotCreateFolder();
        void slotDelete();

    protected:
        void contextMenuEvent( QContextMenuEvent *event );
    
    private:
        void setupUi();
        void setupActions();
        void showContextMenu( const QPoint &globalPos );
        bool canCreateConnection( const QItemSelection &selected );
        bool canCreateFolder( const QItemSelection &selected );
        bool canCreateNote( const QItemSelection &selected );
        bool canDeleteItem( const QItemSelection &selected );
        QModelIndexList selectedIndexes() const;
        QInfinity::NodeItem *nodeItemFromIndex( const QModelIndex &index ) const;

        QAction *quitAction;
        QAction *newConnectionAction;
        QAction *newFolderAction;
        QAction *newNoteAction;
        QAction *deleteAction;
        QTreeView *treeView;
        QInfinity::BrowserModel *fileModel;
        QLabel *statusLabel;
        
};

#endif

