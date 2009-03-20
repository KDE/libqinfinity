#ifndef QINFINITY_TCPCONNECTION_H
#define QINFINITY_TCPCONNECTION_H

#include <libinfinity/common/inf-tcp-connection.h>

#include "qgobject.h"
#include "qtio.h"
#include "ipaddress.h"

#include <QObject>
#include <QPointer>

namespace QInfinity
{

class TcpConnection
    : public QGObject
{
    Q_OBJECT

    public:
        enum Status
        {
            Connecting,
            Connected,
            Closed
        };

        static QPointer<TcpConnection> wrap( InfTcpConnection *infTcpConnection,
            QObject *parent = 0 );

        TcpConnection( const IpAddress &ipAddress,
            unsigned int port,
            QObject *parent = 0,
            bool own_gobject = true );
        ~TcpConnection();

        bool open();
        void close();
        Status status() const;
    
    Q_SIGNALS:
        void statusChanged();

    protected:
        TcpConnection( InfTcpConnection *infTcpConnection,
            QObject *parent = 0 );
    
    private:
        void setupSignals();

        // Signal callbacks
        void emitStatusChanged();
        static void status_changed_cb( InfTcpConnection *connection,
            const char *property,
            void *user_data );
    
};

}

#endif

