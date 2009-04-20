#ifndef QINFINITY_IPADDRESS_H
#define QINFINITY_IPADDRESS_H

#include <QHostAddress>
#include <QString>

typedef struct _InfIpAddress InfIpAddress;

namespace QInfinity
{

/**
 * @brief Creates and stores an ip address.
 */
class IpAddress
{

    public:
        IpAddress( const QHostAddress &address );
        IpAddress( quint32 raw_address );
        IpAddress( const char *address_string );
        ~IpAddress();

        QString toString();
        InfIpAddress *gobject() const;
    
    private:
        InfIpAddress *m_gobject;
};

}

#endif

