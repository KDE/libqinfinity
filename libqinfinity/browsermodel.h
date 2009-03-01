#ifndef QINFINITY_FILE_MODEL_H
#define QINFINITY_FILE_MODEL_H

#include "communicationmanager.h"

#include <QString>
#include <QList>
#include <QStandardItemModel>
#include <QHash>
#include <QPointer>
#include <QAbstractItemView>

namespace QInfinity
{

class ConnectionItem;
class XmlConnection;
class BrowserItemFactory;
class NodeItem;
class ConnectionItem;
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
    
    private:
        XmlConnection *m_xmlConnection;
        Browser *m_browser;
        QHash<unsigned int, NodeItem*> nodeIdToNodeItemMap;

};

/**
 * @brief A model for connections and their file hierarchy
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
    Q_OBJECT

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
         */
        ConnectionItem *addConnection( XmlConnection &connection,
            const QString &name );
        bool hasChildren( const QModelIndex &parent = QModelIndex() ) const;
        /**
         * @brief Add a plugin to connections in this model.
         */
        void addPlugin( NotePlugin &plugin );
        /**
         * @brief Get added plugins.
         */
        const QList<NotePlugin*> plugins() const;
        
        /**
         * @brief Create a subdirectory of parent with name.
         */
        bool createDirectory( QInfinity::NodeItem &parent,
            const QString &name );

    public Q_SLOTS:
        /**
         * @brief Call this when an item has been expanded.
         */
        void itemActivated( const QModelIndex &item = QModelIndex() );

    private Q_SLOTS:
        void slotNodeAdded( const BrowserIter &itr );
        void slotRowsAboutRemoved( const QModelIndex &parent,
            int start,
            int end );

    private:
        void removeConnectionItem( ConnectionItem *item );
        void indexIter( const BrowserIter &iter,
            Browser &browser,
            NodeItem &item );
        NodeItem *itemFromBrowserIter( const BrowserIter &iter,
            Browser &browser );
        NodeItem *indexToNodeItem( const QModelIndex &index ) const;
        Browser *createBrowser( CommunicationManager &commMgr,
            XmlConnection &connection );

        BrowserItemFactory *m_itemFactory;
        QHash<Browser*, ConnectionIndex*> browserToConnectionMap;
        QHash<XmlConnection*, Browser*> connectionToBrowserMap;
        CommunicationManager comm_mgr;
        QList<NotePlugin*> m_plugins;

};

}

#endif

