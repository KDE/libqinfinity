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
        Connection( QInfinity::QtIo &io,
            const QString &hostname,
            unsigned int port,
            QObject *parent = 0 );

        void open();
    
    Q_SIGNALS:
        void connected();
    
    private Q_SLOTS:
        void slotHostnameLookedUp( const QHostInfo &hostInfo );
        void slotXmlConnectionStatusChanged();
        void slotXmlConnectionError( const QString &message );

    private:
        QString hostname;
        unsigned int port;
        QInfinity::QtIo *io;
        QInfinity::TcpConnection *tcpConnection;
        QInfinity::XmppConnection *xmppConnection;

};

class MyBrowser
    : public QObject
{
    Q_OBJECT

    public:
        MyBrowser();

    public Q_SLOTS:
        void connectToHost( const QString &hostname,
            unsigned int port );

    private Q_SLOTS:
        void slotConnectionConnected();
    
    private:
        QInfinity::QtIo io;
        QInfinity::FileModel fileModel;

};

#endif

