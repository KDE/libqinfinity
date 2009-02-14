#ifndef QINFINITY_TEST_CONNECTION_H
#define QINFINITY_TEST_CONNECTION_H

#include "tcpconnection.h"
#include "xmppconnection.h"

#include <QObject>
#include <QString>
#include <QHostInfo>

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
        QString hostname() const;
        QInfinity::XmppConnection &xmppConnection() const;
        QString name() const;
    
    Q_SIGNALS:
        void connected( Connection* );
        void error();
    
    private Q_SLOTS:
        void slotHostnameLookedUp( const QHostInfo &hostInfo );
        void slotXmlConnectionStatusChanged();
        void slotXmlConnectionError( const GError *error );

    private:
        QString m_hostname;
        unsigned int port;
        QInfinity::TcpConnection *tcpConnection;
        QInfinity::XmppConnection *m_xmppConnection;

};

#endif

