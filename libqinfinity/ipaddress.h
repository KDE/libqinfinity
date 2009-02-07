#ifndef QINFINITY_IPADDRESS_H
#define QINFINITY_IPADDRESS_H

#include <libinfinity/common/inf-ip-address.h>

namespace QInfinity
{

/**
 * @brief Creates and stores an ip address.
 */
class IpAddress
{

    public:
        IpAddress( unsigned int raw_address );
        IpAddress( const char *address_string );
        ~IpAddress();

        const char *toString();
        InfIpAddress *gobject() const;
    
    private:
        InfIpAddress *m_gobject;
};

}

#endif

