/*
 * Copyright 2009  Gregory Haynes <greg@greghaynes.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QINFINITY_BROWSER_H
#define QINFINITY_BROWSER_H

#include "qgobject.h"
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
class NotePlugin;
class SessionProxy;
class Session;
class AbstractTextBuffer;
class NodeRequest;

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
        Browser( CommunicationManager& comm_manager,
            XmlConnection* connection,
            QObject *parent = 0 );

        /**
         * @brief Get the connection status of the underlying infinity browser object.
         */
        InfcBrowserStatus connectionStatus();

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
        NodeRequest* addSubdirectory( BrowserIter parent,
            const char *name );

        /**
         * @brief Create a new note.
         * @param parent Parent node of new note.
         * @param name Name of new note.
         * @param plugin Plugin used for note.
         * @param initial_subscribe Subscribe to note on creation.
         */
        NodeRequest* addNote( BrowserIter parent,
            const char *name,
            NotePlugin &plugin,
            bool initial_subscribe );

        /**
         * @brief Create a new note with specified content.
         * @param parent Parent node of new note.
         * @param name Name of new note.
         * @param plugin Plugin used for note.
         * @param initial_subscribe Subscribe to note on creation.
         */
        NodeRequest* addNoteWithContent( BrowserIter parent,
            const char *name,
            NotePlugin &plugin,
            Session &session,
            bool initial_subscribe );

        /**
         * @brief Delete node.
         * @param node Node to be deleted.
         */
        NodeRequest* removeNode( BrowserIter node );

        /**
         * @brief Subscribe to editing session.
         * @param node Note to subscribe to.
         * @param plugin The plugin used for subscription
         * @param textBuffer The text buffer which will be given to your createSession method as user data
         */
        NodeRequest* subscribeSession( BrowserIter node, NotePlugin* plugin = 0,
                                           QInfinity::AbstractTextBuffer* textBuffer = 0 );

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
         * @brief An error has occured.
         */
        void error( const QInfinity::Browser* self, const QString error );

        /**
         * @brief A node has been created.
         */
        void nodeAdded( const BrowserIter &iter );

        /**
         * @brief A node has been removed.
         */
        void nodeRemoved( const BrowserIter &iter );

        /**
         * @brief The connection status of the browser has changed.
         */
        void statusChanged( InfcBrowserStatus status );

        /**
         * @brief The browser is now fully connected.
         */
        void connectionEstablished( const QInfinity::Browser* self );

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
        void signalStatusChanged( InfcBrowserStatus status );
        void signalError( const QString message );

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
        static void status_changed_cb( InfcBrowser *browser,
            void *user_data );
        static void error_cb( InfcBrowser *browser, const GError *error);

};

}

#endif

