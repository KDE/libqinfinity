#ifndef QINFINITY_FILE_MODEL_H
#define QINFINITY_FILE_MODEL_H

#include "communicationmanager.h"

#include <QString>
#include <QList>
#include <QStandardItemModel>
#include <QMap>
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
 */
class ConnectionIndex
{

    public:
        ConnectionIndex( XmlConnection &connection,
            Browser &browser );

        XmlConnection &connection() const;
        Browser &browser() const;
        NodeItem *itemFromIter( const BrowserIter &iter ) const;
        void indexIter( const BrowserIter &iter,
            NodeItem &node );
    
    private:
        XmlConnection *m_xmlConnection;
        Browser *m_browser;
        QMap<unsigned int, NodeItem*> nodeIdToNodeItemMap;

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
        BrowserModel( QObject *parent = 0 );
        BrowserModel( BrowserItemFactory *itemFactory,
            QObject *parent = 0 );
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
        void removeConnectionIndex( const QModelIndex &index );

    public Q_SLOTS:
        void itemActivated( const QModelIndex &parent = QModelIndex() );

    private Q_SLOTS:
        void slotNodeAdded( const BrowserIter &itr );

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
        QMap<Browser*, ConnectionIndex*> browserToConnectionMap;
        QMap<XmlConnection*, Browser*> connectionToBrowserMap;
        CommunicationManager comm_mgr;
        QList<NotePlugin*> m_plugins;
        QList<Browser*> m_browsers;

};

}

#endif

