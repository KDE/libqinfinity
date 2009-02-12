#ifndef QINFINITY_TEST_GUIBROWSER_H
#define QINFINITY_TEST_GUIBROWSER_H

#include "init.h"
#include "qtio.h"
#include "ipaddress.h"
#include "tcpconnection.h"
#include "xmppconnection.h"
#include "filemodel.h"

#include <QApplication>
#include <QObject>
#include <QList>
#include <QTreeView>
#include <QHostInfo>
#include <QHostAddress>

class Connection
    : public QObject
{
    Q_OBJECT

    public:
        Connection( const QString &hostname,
            unsigned int port,
            QObject *parent = 0 );
        ~Connection();

        void open();
        const QString &hostname() const;
        QInfinity::XmppConnection &xmppConnection() const;
    
    Q_SIGNALS:
        void connected();
    
    private Q_SLOTS:
        void slotHostnameLookedUp( const QHostInfo &hostInfo );
        void slotXmlConnectionStatusChanged();
        void slotXmlConnectionError( const QString &message );

    private:
        QString m_hostname;
        unsigned int port;
        QInfinity::TcpConnection *tcpConnection;
        QInfinity::XmppConnection *m_xmppConnection;

};

class MyBrowser
    : public QObject
{
    Q_OBJECT

    public:
        MyBrowser();
        ~MyBrowser();

    public Q_SLOTS:
        void connectToHost( const QString &hostname,
            unsigned int port );

    private Q_SLOTS:
        void slotConnectionConnected();
    
    private:
        QTreeView *treeView;
        QInfinity::FileModel fileModel;

};

#endif

