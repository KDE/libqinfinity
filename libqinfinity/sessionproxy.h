#ifndef QINFINITY_SESSION_PROXY_H
#define QINFINITY_SESSION_PROXY_H

#include "qgobject.h"

typedef struct _InfcSessionProxy InfSessionProxy;

namespace QInfinity
{

class SessionProxy
    : public QGObject
{

    public:
        SessionProxy( InfSessionProxy *infProxy );
        SessionProxy( const SessionProxy &other );

};

}

#endif

