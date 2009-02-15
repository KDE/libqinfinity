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
class CommunicatonManager;
class NodeItem;
class ConnectionItem;
class Browser;
class BrowserIter;

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
 */
class BrowserModel
    : public QStandardItemModel
{
    Q_OBJECT

    public:
        BrowserModel( QObject *parent = 0 );
        BrowserModel( BrowserItemFactory *itemFactory,
            QObject *parent = 0 );
        BrowserModel( QList<XmlConnection*> connections,
            QObject *parent = 0 );
        BrowserModel( BrowserItemFactory *itemFactory,
            QList<XmlConnection*> connections,
            QObject *parent = 0 );
        ~BrowserModel();

        /**
         * @brief Use factory for creating items.
         *
         * If factory is NULL then BrowserItemFactory is used.
         * factory will be reparented.
         */
        void setItemFactory( BrowserItemFactory *factory );
        BrowserItemFactory &itemFactory() const;
        /**
         * @brief Add connection with name for model to represent.
         * @return ConnectionItem representing connection.
         */
        ConnectionItem *addConnection( XmlConnection &connection,
            const QString &name );
        const QList<XmlConnection*> connections() const;
        bool hasChildren( const QModelIndex &parent = QModelIndex() ) const;

    public Q_SLOTS:
        void itemActivated( const QModelIndex &parent = QModelIndex() );

    private Q_SLOTS:
        void slotNodeAdded( const BrowserIter &itr );

    private:
        void indexIter( const BrowserIter &iter,
            Browser &browser,
            NodeItem &item );
        NodeItem *itemFromBrowserIter( const BrowserIter &iter,
            Browser &browser );
        NodeItem *indexToNodeItem( const QModelIndex &index ) const;

        BrowserItemFactory *m_itemFactory;
        QList<XmlConnection*> m_connections;
        QMap<Browser*, ConnectionIndex*> browserToConnectionMap;
        CommunicationManager comm_mgr;

};

}

#endif

