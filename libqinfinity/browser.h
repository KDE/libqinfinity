#ifndef QINFINITY_BROWSER_H
#define QINFINITY_BROWSER_H

#include "qgobject.h"
#include "sessionproxy.h"
#include "noteplugin.h"
#include "browseriter.h"

#include <QPointer>

typedef struct _InfcBrowser InfcBrowser;
typedef struct _InfcBrowserIter InfcBrowserIter;
typedef struct _InfcExploreRequest InfcExploreRequest;
typedef struct _InfcNodeRequest InfcNodeRequest;
typedef struct _InfcSessionProxy InfcSessionProxy;

class QObject;

namespace QInfinity
{

class QtIo;
class CommunicationManager;
class XmlConnection;

/**
 * @brief Browse an infinote server.
 *
 * The Browser contains functionality related to navigating
 * and monitoring nodes on an infinote server.  To navigate
 * the nodes on a server, use a BrowserIter.
 *
 * The BrowserModel is also useful for remote server browsing.
 */
class Browser
    : public QGObject
{
    Q_OBJECT;

    public:
        static QPointer<Browser> wrap( InfcBrowser *infBrowser,
            QObject *parent = 0,
            bool own_gobject = true );

        /**
         * @brief Create Browser for connection.
         */
        Browser( CommunicationManager &comm_manager,
            XmlConnection &connection,
            QObject *parent = 0 );

        /**
         * @brief Add plugin to browser session.
         */
        bool addPlugin( NotePlugin &plugin );

        /**
         * @brief Create a new subdirectiory.
         * @param parent Parent of new directory.
         * @param name Name of new directory.
         * @return Request for monitoring node creation.
         */
        InfcNodeRequest *addSubdirectory( BrowserIter parent,
            const char *name );

        /**
         * @brief Create a new note.
         * @param parent Parent of new note.
         * @param name Name of new note.
         * @param plugin Plugin used for note.
         * @param initial_subscribe Subscribe to note on creation.
         */
        InfcNodeRequest *addNote( BrowserIter parent,
            const char *name,
            NotePlugin &plugin,
            bool initial_subscribe );

        /**
         * @brief Delete node.
         * @param node Node to be deleted.
         */
        InfcNodeRequest *removeNode( BrowserIter node );

        /**
         * @brief Subscribe to editing session.
         * @param node Note to subscribe to.
         */
        InfcNodeRequest *subscribeSession( BrowserIter node );

    protected:
        Browser( InfcBrowser *infBrowser,
            QObject *parent = 0,
            bool own_gobject = true );
    
    Q_SIGNALS:
        /**
         * @brief A subdirectory has begun to be explored.
         *
         * The iter is only valid for the life of the signal
         * handler.
         */
        void beginExplore( const BrowserIter &iter,
            InfcExploreRequest *request );

        /**
         * @brief A subscription request has been made.
         * @param iter Iter pointing to nobe subscribed to.
         * @param request Request for the operation.
         *
         * The iter is only valid for the life of the signal
         * handler
         */
        void beginSubscribe( const BrowserIter &iter,
            InfcNodeRequest *request );

        /**
         * @brief A subscription to a note has been made.
         *
         * This does not mean the session is running.  The
         * session is likely still synchronizing.
         */
        void subscribeSession( const QInfinity::BrowserIter &iter,
            QPointer<QInfinity::SessionProxy> proxy );

        /**
         * @brief A node has been created.
         */
        void nodeAdded( const BrowserIter &iter );

        /**
         * @brief A node has been removed.
         */
        void nodeRemoved( const BrowserIter &iter );

    private:
        void setupSignals();

        void signalBeginExplore( InfcBrowserIter *infIter,
            InfcExploreRequest *request );
        void signalBeginSubscribe( InfcBrowserIter *iter,
            InfcNodeRequest *request );
        void signalSubscribeSession( InfcBrowserIter *infIter,
            InfcSessionProxy *proxy );
        void signalNodeAdded( InfcBrowserIter *infIter );
        void signalNodeRemoved( InfcBrowserIter *infIter );

        static void begin_explore_cb( InfcBrowser *browser,
            InfcBrowserIter *iter,
            InfcExploreRequest *request,
            void *user_data );
        static void begin_subscribe_cb( InfcBrowser *browser,
            InfcBrowserIter *iter,
            InfcNodeRequest *request,
            void *user_data );
        static void subscribe_session_cb( InfcBrowser *browser,
            InfcBrowserIter *iter,
            InfcSessionProxy *proxy,
            void *user_data );
        static void node_added_cb( InfcBrowser *browser,
            InfcBrowserIter *iter,
            void *user_data );
        static void node_removed_cb( InfcBrowser *browser,
            InfcBrowserIter *iter,
            void *user_data );

};

}

#endif

