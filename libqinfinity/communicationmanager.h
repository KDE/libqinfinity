#ifndef QINFINITY_COMMUNICATION_MANAGER_H
#define QINFINITY_COMMUNICATION_MANAGER_H

#include "qgobject.h"

#include <QObject>
#include <QPointer>

typedef struct _InfCommunicationManager InfCommunicationManager;

namespace QInfinity
{

/**
 * @brief Manages multiple communication sessions.
 */
class CommunicationManager
    : public QGObject
{

    public:
        /**
         * @brief Create manager making use of object store.
         */
        static QPointer<CommunicationManager> wrap( InfCommunicationManager *infCommManager,
            QObject *parent = 0,
            bool own_gobject = true );

        CommunicationManager( QObject *parent = 0, bool own_gobject = true );
        CommunicationManager( const CommunicationManager &other );

    protected:
        /**
         * @brief Create a new Communication Manager.
         * @param own_gobject Take ownership of the created GObject.
         *
         * The own_gobject parameter specifies if the created GObject will be
         * deleted when the CommunicationManager is deleted.  If you dont want
         * to store this CommunicationManager, you can set this to false.
         */
        CommunicationManager( InfCommunicationManager *infCommManager,
            QObject *parent = 0,
            bool own_gobject = true );

};

}

#endif

