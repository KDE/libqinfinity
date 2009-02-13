#ifndef QINFINITY_BROWSER_H
#define QINFINITY_BROWSER_H

#include "qgobject.h"
#include "sessionproxy.h"

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
class BrowserIter;

/**
 * @brief Browse an infinote server.
 *
 * The Browser contains functionality related to navigating
 * and monitoring nodes on an infinote server.  To navigate
 * the nodes on a server, use BrowserIter.
 */
class Browser
    : public QGObject
{
    Q_OBJECT

    public:
        Browser( CommunicationManager &comm_manager,
            XmlConnection &connection,
            QObject *parent = 0 );
    
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
        void subscribeSession( const BrowserIter &iter,
            SessionProxy proxy );
        void nodeAdded( const BrowserIter &iter );
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

