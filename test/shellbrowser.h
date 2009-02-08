#ifndef QINFINITY_TEST_CLIENTBROWSER_H
#define QINFINITY_TEST_CLIENTBROWSER_H

#include "init.h"
#include "tcpconnection.h"
#include "xmppconnection.h"
#include "communicationmanager.h"
#include "browser.h"

#include <QObject>
#include <QApplication>

#include <iostream>

class MyBrowser
    : public QObject
{
    Q_OBJECT

    public:
        MyBrowser( QInfinity::QtIo &io );
        ~MyBrowser();
    
    public Q_SLOTS:
        void statusChanged();

    private:
        void setupSignals();

        QInfinity::QtIo *m_io;
        QInfinity::TcpConnection *connection;
        QInfinity::XmppConnection *xmppConnection;
        QInfinity::CommunicationManager *commMgr;
        QInfinity::Browser *browser;

};

#endif

