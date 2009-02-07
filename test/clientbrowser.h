#ifndef QINFINITY_TEST_CLIENTBROWSER_H
#define QINFINITY_TEST_CLIENTBROWSER_H

#include "init.h"
#include "tcpconnection.h"

#include <QObject>
#include <QApplication>

#include <iostream>

class MyBrowser
    : public QObject
{
    Q_OBJECT

    public:
        MyBrowser( QInfinity::QtIo &io );
    
    public Q_SLOTS:
        void statusChanged();

    private:
        void setupSignals();

        QInfinity::QtIo *m_io;
        QInfinity::TcpConnection *connection;

};

#endif

