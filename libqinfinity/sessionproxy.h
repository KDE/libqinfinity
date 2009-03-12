#ifndef QINFINITY_SESSION_PROXY_H
#define QINFINITY_SESSION_PROXY_H

#include "qgobject.h"

#include <QObject>

typedef struct _InfcSessionProxy InfSessionProxy;
typedef struct _InfSession InfSession;
typedef struct _InfcUserRequest InfcUserRequest;
typedef struct _GParameter GParameter;

namespace QInfinity
{

class Session;

/**
 * @brief Used for retrieving newly created sessions.
 */
class SessionProxy
    : public QGObject
{

    public:
        SessionProxy( InfSessionProxy *infProxy,
            QObject *parent = 0 );
        SessionProxy( const SessionProxy &other,
            QObject *parent = 0 );

        InfcUserRequest *joinUser( const GParameter *params,
            unsigned int n_params,
            GError **error );

        /**
         * @brief Get the session for this proxy.
         *
         * If your session is not of the type you expected,
         * you probably need to be using a NotePlugin.  See
         * the NotePlugin documentation for more information.
         */
        Session *session() const;

};

}

#endif

