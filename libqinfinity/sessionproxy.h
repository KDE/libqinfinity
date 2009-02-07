#ifndef QINFINITY_SESSION_PROXY_H
#define QINFINITY_SESSION_PROXY_H

#include "qgobject.h"

typedef struct _InfcSessionProxy InfSessionProxy;
typedef struct _InfSession InfSession;
typedef struct _InfcUserRequest InfcUserRequest;
typedef struct _GParameter GParameter;

namespace QInfinity
{

class SessionProxy
    : public QGObject
{

    public:
        SessionProxy( InfSessionProxy *infProxy );
        SessionProxy( const SessionProxy &other );

        InfcUserRequest *joinUser( const GParameter *params,
            unsigned int n_params,
            GError **error );
        InfSession *session() const;

};

}

#endif

