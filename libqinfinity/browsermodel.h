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

#ifndef QINFINITY_FILE_MODEL_H
#define QINFINITY_FILE_MODEL_H

#include "communicationmanager.h"

#include <QString>
#include <QList>
#include <QStandardItemModel>
#include <QHash>
#include <QPointer>

namespace QInfinity
{

class ConnectionItem;
class XmlConnection;
class BrowserItemFactory;
class NodeItem;
class Browser;
class BrowserIter;
class NotePlugin;

/**
 * @brief Manages data tied to a connection
 *
 * This class will take ownership of its browser.
 */
class ConnectionIndex
{

    public:
        ConnectionIndex( XmlConnection &connection,
            Browser &browser );
        ~ConnectionIndex();

        XmlConnection &connection() const;
        Browser &browser() const;
        NodeItem *itemFromIter( const BrowserIter &iter ) const;
        void indexIter( const BrowserIter &iter,
            NodeItem &node );
        void removeIter( const BrowserIter &iter );
    
    private:
        XmlConnection *m_xmlConnection;
        Browser *m_browser;
        QHash<unsigned int, NodeItem*> nodeIdToNodeItemMap;

};

/**
 * @brief A model representing connections and their available files
 *
 * The BrowserModel provides a model containing connections
 * added with BrowserModel::addConnection.  Add the plugins
 * you wish to use with BrowserModel::addPlugin to allow
 * them to be added each connections' Browser.  You must also
 * call BrowserModel::itemActivated on a directory for it to
 * become populated.  This is usually done by connecting
 * signals from a view to the BrowserModel::itemActivated.
 */
class BrowserModel
    : public QStandardItemModel
{
    Q_OBJECT;

    public:
        /**
         * @brief Create a new BrowserModel
         */
        BrowserModel( QObject *parent = 0 );

        /**
         * @brief Create BrowserModel with specified BrowserItemFactory
         */
        BrowserModel( BrowserItemFactory *itemFactory,
            QObject *parent = 0 );

        /**
         * @brief Destroy the BrowserModel
         */
        ~BrowserModel();

        /**
         * @brief Use factory for creating items.
         *
         * If factory is NULL then BrowserItemFactory is used.
         * factory will be reparented.
         */
        void setItemFactory( BrowserItemFactory *factory );

        /**
         * @brief Get factory used by this model.
         */
        BrowserItemFactory &itemFactory() const;

        /**
         * @brief Add connection with name for model to represent.
         * @return ConnectionItem representing connection.
         *
         * The connection will be reparented to the BrowserModel.
         * You can remove the connection by removing the appropriate
         * row from the model.
         */
        ConnectionItem *addConnection( XmlConnection &connection,
            const QString &name );

        bool hasChildren( const QModelIndex &parent = QModelIndex() ) const;

        /**
         * @brief Add a plugin to connections in this model.
         *
         * The plugin will be reparented.
         */
        void addPlugin( NotePlugin &plugin );

        /**
         * @brief Get added plugins.
         */
        QList<NotePlugin*> plugins() const;

        /**
         * @brief Get the current browsers
         */
        QList<Browser*> browsers() const;
        
        /**
         * @brief Create a directory on the server.
         */
        bool createDirectory( const QModelIndex &parent,
            const QString &name );

        /**
         * @brief Create a note of type plugin on the server.
         */
        bool createNote( const QModelIndex &parent,
            NotePlugin &plugin,
            const QString &name );

        bool removeRows( int row, int count,
            const QModelIndex &parent );

    Q_SIGNALS:
        void browserAdded( QInfinity::Browser &browser );

    public Q_SLOTS:
        /**
         * @brief Call this when an item has been expanded.
         */
        void itemActivated( const QModelIndex &item = QModelIndex() );

    private Q_SLOTS:
        void slotNodeAdded( const BrowserIter &itr );
        void slotNodeRemoved( const BrowserIter &itr );

    private:
        void removeConnectionItem( ConnectionItem *item );
        void deleteNodeItem( NodeItem *item );
        void indexIter( const BrowserIter &iter,
            Browser &browser,
            NodeItem &item );
        void removeIterIndex( const BrowserIter &iter,
            Browser &browser );
        NodeItem *itemFromBrowserIter( const BrowserIter &iter,
            Browser &browser );
        NodeItem *indexToNodeItem( const QModelIndex &index ) const;
        Browser *createBrowser( CommunicationManager &commMgr,
            XmlConnection &connection );

        BrowserItemFactory *m_itemFactory;
        QHash<Browser*, ConnectionIndex*> browserToConnectionMap;
        CommunicationManager comm_mgr;
        QList<NotePlugin*> m_plugins;
        QList<Browser*> m_browsers;

};

}

#endif

