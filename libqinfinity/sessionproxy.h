#ifndef QINFINITY_SESSION_PROXY_H
#define QINFINITY_SESSION_PROXY_H

#include "qgobject.h"

#include <QObject>
#include <QPointer>

typedef struct _InfcSessionProxy InfcSessionProxy;
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
        static QPointer<SessionProxy> wrap( InfcSessionProxy *infObject,
            QObject *parent,
            bool own_gobject = true );

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
        QPointer<Session> session() const;

    protected:
        SessionProxy( InfcSessionProxy *infProxy,
            QObject *parent = 0,
            bool own_gobject = true );

};

}

#endif

