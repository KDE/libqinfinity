#ifndef QINFINITY_TEST_GUIBROWSER_H
#define QINFINITY_TEST_GUIBROWSER_H

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

        void setup();
    
    Q_SIGNALS:
        void hostnameLookedUp( const QHostAddress &address,
            unsigned int port );
    
    private Q_SLOTS:
        void slotHostnameLookedUp( const QHostInfo &hostInfo );

    private:
        QString hostname;
        unsigned int port;

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
        void connectToHost( const QHostAddress &address,
            unsigned int port );

    private Q_SLOTS:
        void slotConnectionStatusChanged();
    
    private:
        QInfinity::QtIo io;
        QInfinity::FileModel fileModel;

};

#endif

