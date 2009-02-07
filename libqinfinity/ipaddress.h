#ifndef QINFINITY_IPADDRESS_H
#define QINFINITY_IPADDRESS_H

#include "qgobject.h"

#include <libinfinity/common/inf-ip-address.h>

namespace QInfinity
{

/**
 * @brief Creates and stores an ip address.
 */
class IpAddress
    : public QGObject
{

    public:
        IpAddress( unsigned int raw_address );
        IpAddress( const char *address_string );

        const char *toString();
};

}

#endif

