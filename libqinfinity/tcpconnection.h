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

    public:
        TcpConnection( QtIo &io,
            IpAddress &ipAddress,
            QObject *parent = 0 );
    
};

}

#endif

