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

#include "browsermodel.h"
#include "browser.h"
#include "xmlconnection.h"
#include "tcpconnection.h"
#include "browseritemfactory.h"
#include "noteplugin.h"

#include <QDebug>

#include "browsermodel.moc"

namespace QInfinity
{

class BrowserModelPrivate
{

    public:
        BrowserItemFactory *itemFactory;
        QHash<const Browser*, ConnectionIndex*> browserToConnectionMap;
        CommunicationManager comm_mgr;
        QList<NotePlugin*> plugins;
        QList<Browser*> browsers;

};

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

ConnectionIndex::ConnectionIndex( XmlConnection &connection,
    Browser &browser )
    : m_xmlConnection( &connection )
    , m_browser( &browser )
{
}

ConnectionIndex::~ConnectionIndex()
{
    QInfinity::TcpConnection *tcpConn;
    delete m_browser;
    tcpConn = m_xmlConnection->tcpConnection();
    delete m_xmlConnection;
    delete tcpConn;
}

XmlConnection &ConnectionIndex::connection() const
{
    return *m_xmlConnection;
}

Browser &ConnectionIndex::browser() const
{
    return *m_browser;
}

NodeItem *ConnectionIndex::itemFromIter( const BrowserIter &iter ) const
{
    if( nodeIdToNodeItemMap.contains( iter.infBrowserIter()->node_id ) )
        return nodeIdToNodeItemMap[iter.infBrowserIter()->node_id];
    else
        return 0;
}

void ConnectionIndex::indexIter( const BrowserIter &iter,
    NodeItem &node )
{
    nodeIdToNodeItemMap[iter.infBrowserIter()->node_id] = &node;
}

void ConnectionIndex::removeIter( const BrowserIter &iter )
{
    nodeIdToNodeItemMap.remove(iter.infBrowserIter()->node_id);
}

BrowserModel::BrowserModel( QObject *parent )
    : QStandardItemModel( parent )
    , d_ptr( new BrowserModelPrivate )
{
    Q_D(BrowserModel);
    
    d->itemFactory = new BrowserItemFactory;
    QStringList headerlabels;
    headerlabels.append( tr("Name") );
    setHorizontalHeaderLabels( headerlabels );
}

BrowserModel::BrowserModel( BrowserItemFactory *itemFactory,
    QObject *parent )
    : QStandardItemModel( parent )
    , d_ptr( new BrowserModelPrivate )
{
    Q_D(BrowserModel);
    
    d->itemFactory = itemFactory;
    if( !d->itemFactory)
        d->itemFactory = new BrowserItemFactory;
    d->itemFactory->setParent( this );
}

BrowserModel::~BrowserModel()
{
    Q_D(BrowserModel);
    
    QList<ConnectionIndex*> connIdexes;
    ConnectionIndex *index;
    connIdexes = d->browserToConnectionMap.values();
    
    foreach(index, connIdexes)
        delete index;
    delete d->itemFactory;
    delete d;
}

void BrowserModel::setItemFactory( BrowserItemFactory *factory )
{
    Q_D(BrowserModel);
    
    if( !factory )
        return;

    d->itemFactory = factory;
}

ConnectionItem *BrowserModel::addConnection( XmlConnection* connection,
    const QString &name )
{
    Q_D(BrowserModel);
    
    Browser *browser;
    ConnectionIndex *index;
    ConnectionItem *connItem;
    NotePlugin* plugin;

    connection->setParent( this );

    // Create and initialive a new browser
    browser = createBrowser( d->comm_mgr, connection );
    foreach( plugin, plugins() )
        browser->addPlugin( *plugin );
    index = new ConnectionIndex( *connection, *browser );
    d->browserToConnectionMap[browser] = index;
    connect( browser, SIGNAL(nodeAdded( const BrowserIter&)),
        this, SLOT(slotNodeAdded( const BrowserIter&)) );
    connect( browser, SIGNAL(nodeRemoved( const BrowserIter& )),
        this, SLOT(slotNodeRemoved( const BrowserIter& )) );
    connect( browser, SIGNAL(connectionEstablished(const QInfinity::Browser*)),
        this, SLOT(connectionEstablished(const QInfinity::Browser*)) );

    connItem = d->itemFactory->createConnectionItem( *connection,
        *browser,
        name );
    connItem->setParent( this );
    insertRow( 0, connItem );
    emit( connectionAdded( connection ) );
    return connItem;
}

void BrowserModel::connectionEstablished(const Browser* browser)
{
    Q_D(BrowserModel);

    qDebug() << "CONNECTION ESTABLISHED";
    NodeItem *nodeItem;
    BrowserIter rootNode( *browser );
    nodeItem = d->itemFactory->createRootNodeItem( rootNode );
    for ( int i = 0; i < rowCount(QModelIndex()); i++ ) {
        QInfinity::ConnectionItem* connItem = dynamic_cast<QInfinity::ConnectionItem*>(itemFromIndex(index(i, 0, QModelIndex())));
        if ( connItem && connItem->browser() == browser ) {
            indexIter( rootNode, browser, *nodeItem );
            connItem->setChild( 0, nodeItem );
            break;
        }
    }
}

bool BrowserModel::hasChildren( const QModelIndex &parent ) const
{
    if( !parent.isValid() )
        return true;
    QStandardItem *stdItem = itemFromIndex(parent);
    NodeItem *nodeItem;

    if( stdItem->type() == BrowserItemFactory::ConnectionItem )
    {
        return true;
    }
    if( stdItem->type() == BrowserItemFactory::NodeItem )
    {
        nodeItem = dynamic_cast<NodeItem*>(stdItem);
        return nodeItem->isDirectory();
    }

    return false;
}

void BrowserModel::addPlugin( NotePlugin &plugin )
{
    Q_D(BrowserModel);
    
    plugin.setParent( this );
    ConnectionIndex *index;
    foreach( index, d->browserToConnectionMap.values() )
        index->browser().addPlugin( plugin );
    d->plugins.append( &plugin );
}

QList<NotePlugin*> BrowserModel::plugins() const
{
    Q_D(const BrowserModel);
    
    return d->plugins;
}

QList<Browser*> BrowserModel::browsers() const
{
    Q_D(const BrowserModel);
    
    return d->browsers;
}

bool BrowserModel::createDirectory( const QModelIndex &parent,
    const QString &name )
{
    NodeItem *parentItem;
    Browser *browser;

    parentItem = indexToNodeItem( parent );
    if( !parentItem )
    {
        qDebug() << "Parent not a node item.";
        return false;
    }
    if( !parentItem->isDirectory() )
    {
        qDebug() << "Cannot create folder with parent not a directory.";
        return false;
    }
    browser = parentItem->iter().browser();
    if( !browser )
    {
        qDebug() << "Could not find parent items' browser.";
        return false;
    }
    return browser->addSubdirectory( parentItem->iter(), name.toAscii() );
}

bool BrowserModel::createNote( const QModelIndex &parent,
    NotePlugin &plugin,
    const QString &name )
{
    NodeItem *parentItem;
    Browser *browser;

    parentItem = indexToNodeItem( parent );
    if( !parentItem )
    {
        qDebug() << "Parent not a node item.";
        return false;
    }
    if( !parentItem->isDirectory() )
    {
        qDebug() << "Cannot create note unless parent is a directory.";
        return false;
    }
    browser = parentItem->iter().browser();
    if( !browser )
    {
        qDebug() << "Could not find parent items' browser.";
        return false;
    }
    browser->addNote( parentItem->iter(), name.toAscii(), plugin, false );
    return true;
}

bool BrowserModel::removeRows( int row, int count,
    const QModelIndex &parent )
{
    int i;
    QStandardItem *item;
    QModelIndex curIndex;
    for( i = 0; i < count; i++ )
    {
        curIndex = index( row + i, 0, parent );
        item = itemFromIndex( curIndex );
        if( item )
        {
            if( item->type() == BrowserItemFactory::ConnectionItem )
            {
                beginRemoveRows( parent, item->row(), item->row() );
                removeConnectionItem( dynamic_cast<ConnectionItem*>(item) );
                endRemoveRows();
            }
            else
                deleteNodeItem( dynamic_cast<NodeItem*>(item) );
        }
        else
        {
            qDebug() << "Could not locate item to remove.";
        }
    }
    return true;
}

CommunicationManager &BrowserModel::communicationManager()
{
    Q_D(BrowserModel);
    return d->comm_mgr;
}

void BrowserModel::itemActivated( const QModelIndex &parent )
{
    if( !parent.isValid() )
        return;
    QStandardItem *stdItem = itemFromIndex(parent);
    
    if( stdItem->type() == BrowserItemFactory::NodeItem )
        dynamic_cast<NodeItem*>(stdItem)->activate();
}

void BrowserModel::slotNodeAdded( const BrowserIter &itr )
{
    Q_D(BrowserModel);
    
    NodeItem *item, *parentItem;
    Browser *browser;
    BrowserIter parentItr( itr );

    item = d->itemFactory->createNodeItem( itr );
    browser = dynamic_cast<Browser*>(sender());
    indexIter( itr, browser, *item );

    parentItr.parent();
    parentItem = itemFromBrowserIter( parentItr, *browser );
    if( !parentItem )
    {
        qDebug() << "Couldnt find parent to add node to.";
        return;
    }
    parentItem->insertRow( 0, item );
}

void BrowserModel::slotNodeRemoved( const BrowserIter &itr )
{
    qDebug() << "Removing node";
    NodeItem *nodeItem = itemFromBrowserIter( itr, *itr.browser() );
    if( !nodeItem )
    {
        qDebug() << "Couldnt find item in model to remove! "
            << " The browsing model may be inconsistent!";
        return;
    }
    QStandardItemModel::removeRows( nodeItem->row(), 1, nodeItem->parent()->index() );
    removeIterIndex( itr, itr.browser() );
}

void BrowserModel::removeConnectionItem( ConnectionItem *item )
{
    Q_D(BrowserModel);
    
    if( !item )
    {
        qDebug() << "Cant remove null connection item.";
        return;
    }
    ConnectionIndex *index;
    index = d->browserToConnectionMap[item->browser()];
    d->browserToConnectionMap.remove(item->browser());
    emit( connectionRemoved( item->connection() ) );
    delete index;
}

void BrowserModel::deleteNodeItem( NodeItem *item )
{
    QPointer<Browser> browser = item->iter().browser();
    browser->removeNode( item->iter() );
}

void BrowserModel::indexIter( const BrowserIter &iter,
    const Browser* browser,
    NodeItem &item )
{
    Q_D(BrowserModel);
    ConnectionIndex *index;

    index = d->browserToConnectionMap[browser];
    if(index)
        index->indexIter( iter, item );
}

void BrowserModel::removeIterIndex( const BrowserIter &iter,
    const Browser* browser )
{
    Q_D(BrowserModel);
    ConnectionIndex *index;

    index = d->browserToConnectionMap[browser];
    if(index)
        index->removeIter( iter );
}

NodeItem *BrowserModel::itemFromBrowserIter( const BrowserIter &iter,
    Browser &browser )
{
    Q_D(BrowserModel);
    ConnectionIndex *index;
    
    index = d->browserToConnectionMap[&browser];
    if(index)
        return index->itemFromIter( iter );
    return 0;
}

NodeItem *BrowserModel::indexToNodeItem( const QModelIndex &item ) const
{
    if( !item.isValid() )
    {
        qDebug() << "Root item is not a node.";
        return 0;
    }
    QStandardItem *stdItem = itemFromIndex( item );
    if( stdItem->type() == BrowserItemFactory::NodeItem )
        return dynamic_cast<NodeItem*>(stdItem);
    else
    {
        qDebug() << "Cannot convert to NodeItem non NodeItem type.";
        return 0;
    }
}

/*
 * Creates a browser and adds all plugins to it.
 */
Browser *BrowserModel::createBrowser( CommunicationManager& commMgr,
    XmlConnection* connection )
{
    Q_D(BrowserModel);
    
    Browser *browser = new Browser( commMgr, connection, this );
    QList<NotePlugin*> pluginList = plugins();
    QList<NotePlugin*>::Iterator itr;
    for( itr = pluginList.begin(); itr != pluginList.end(); itr++ )
    {
        browser->addPlugin( **itr );
    }
    d->browsers.append( browser );
    emit( browserAdded( *browser ) );
    return browser;
}

}

