#ifndef QINFINITY_COMMUNICATION_MANAGER_H
#define QINFINITY_COMMUNICATION_MANAGER_H

#include "qgobject.h"

#include <QObject>

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
        static CommunicationManager *create( QObject *parent = 0,
            bool own_gobject = true );
        /**
         * @brief Create manager making use of object store.
         */
        static CommunicationManager *create( InfCommunicationManager *inf_mgr,
            QObject *parent = 0,
            bool own_gobject = true );

        /**
         * @brief Create a new Communication Manager.
         * @param own_gobject Take ownership of the created GObject.
         *
         * The own_gobject parameter specifies if the created GObject will be
         * deleted when the CommunicationManager is deleted.  If you dont want
         * to store this CommunicationManager, you can set this to false.
         */
        CommunicationManager( QObject *parent = 0, bool own_gobject = true  );
        CommunicationManager( InfCommunicationManager *infCommManager, QObject *parent = 0 );
        CommunicationManager( const CommunicationManager &other );

};

}

#endif

