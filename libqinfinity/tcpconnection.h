#ifndef QINFINITY_TCPCONNECTION_H
#define QINFINITY_TCPCONNECTION_H

#include <libinfinity/common/inf-tcp-connection.h>

#include "qgobject.h"
#include "qtio.h"
#include "ipaddress.h"

#include <QObject>

namespace QInfinity
{

class TcpConnection
    : public QObject
    , public QGObject
{
    Q_OBJECT

    public:
        enum Status
        {
            Connecting,
            Connected,
            Closed
        };

        TcpConnection( QtIo &io,
            const IpAddress &ipAddress,
            unsigned int port,
            QObject *parent = 0 );

        bool open();
        void close();
        Status getStatus() const;
    
    Q_SIGNALS:
        void statusChanged();
    
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

