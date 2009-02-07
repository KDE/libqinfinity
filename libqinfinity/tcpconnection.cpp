#include "tcpconnection.h"

namespace QInfinity
{

TcpConnection::TcpConnection( QtIo &io,
    IpAddress &address,
    QObject *parent )
    : QObject( parent )
{
    InfTcpConnection *infObject;

    infObject = INF_TCP_CONNECTION(g_object_new( INF_TYPE_TCP_CONNECTION, NULL ));
    setGobject( G_OBJECT(infObject) );
}

}

