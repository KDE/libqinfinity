#ifndef QINFINITY_SESSION_H
#define QINFINITY_SESSION_H

#include "qgobject.h"
#include "communicationmanager.h"

#include <QObject>

typedef struct _InfSession InfSession;

namespace QInfinity
{

class CommunicationManager;

class Session
    : public QObject
    , public QGObject
{

    public:
        Session( InfSession *infSession,
            QObject *parent = 0 );

        CommunicationManager communicationManager() const;
        
};

}

#endif

