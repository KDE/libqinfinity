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

ConnectionIndex::ConnectionIndex( XmlConnection &connection,
    Browser &browser )
    : m_xmlConnection( &connection )
    , m_browser( &browser )
{
}

ConnectionIndex::~ConnectionIndex()
{
    qDebug() << "deleting connection";
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
    , m_itemFactory( new BrowserItemFactory )
{
    QStringList headerlabels;
    headerlabels.append( tr("Name") );
    setHorizontalHeaderLabels( headerlabels );
}

BrowserModel::BrowserModel( BrowserItemFactory *itemFactory,
    QObject *parent )
    : QStandardItemModel( parent )
    , m_itemFactory( itemFactory )
{
    if( !m_itemFactory)
        m_itemFactory = new BrowserItemFactory;
    m_itemFactory->setParent( this );
}

BrowserModel::~BrowserModel()
{
    QList<ConnectionIndex*> connIdexes;
    ConnectionIndex *index;
    connIdexes = browserToConnectionMap.values();
    
    foreach(index, connIdexes)
        delete index;
    delete m_itemFactory;
}

void BrowserModel::setItemFactory( BrowserItemFactory *factory )
{
    if( !factory )
        return;

    m_itemFactory = factory;
}

ConnectionItem *BrowserModel::addConnection( XmlConnection &connection,
    const QString &name )
{
    Browser *browser;
    ConnectionIndex *index;
    ConnectionItem *connItem;
    NodeItem *nodeItem;
    NotePlugin* plugin;

    connection.setParent( this );

    // Create and initialive a new browser
    browser = createBrowser( comm_mgr, connection );
    foreach( plugin, plugins() )
        browser->addPlugin( *plugin );
    index = new ConnectionIndex( connection, *browser );
    browserToConnectionMap[browser] = index;
    connect( browser, SIGNAL(nodeAdded( const BrowserIter&)),
        this, SLOT(slotNodeAdded( const BrowserIter&)) );
    connect( browser, SIGNAL(nodeRemoved( const BrowserIter& )),
        this, SLOT(slotNodeRemoved( const BrowserIter& )) );

    connItem = m_itemFactory->createConnectionItem( connection,
        *browser,
        name );
    connItem->setParent( this );
    insertRow( 0, connItem );
    BrowserIter rootNode( *browser );
    nodeItem = m_itemFactory->createRootNodeItem( rootNode );
    indexIter( rootNode, *browser, *nodeItem );
    connItem->setChild( 0, nodeItem );
    return connItem;
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
    plugin.setParent( this );
    ConnectionIndex *index;
    foreach( index, browserToConnectionMap.values() )
        index->browser().addPlugin( plugin );
    m_plugins.append( &plugin );
}

QList<NotePlugin*> BrowserModel::plugins() const
{
    return m_plugins;
}

QList<Browser*> BrowserModel::browsers() const
{
    return m_browsers;
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
    qDebug() << "Remove rows";
    int i;
    QStandardItem *item, *parentItem;
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
    NodeItem *item, *parentItem;
    Browser *browser;
    BrowserIter parentItr( itr );

    item = m_itemFactory->createNodeItem( itr );
    browser = dynamic_cast<Browser*>(sender());
    indexIter( itr, *browser, *item );

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
    removeIterIndex( itr, *itr.browser() );
}

void BrowserModel::removeConnectionItem( ConnectionItem *item )
{
    if( !item )
    {
        qDebug() << "Cant remove null connection item.";
        return;
    }
    ConnectionIndex *index;
    index = browserToConnectionMap[&item->browser()];
    browserToConnectionMap.remove(&item->browser());
    delete index;
}

void BrowserModel::deleteNodeItem( NodeItem *item )
{
    QPointer<Browser> browser = item->iter().browser();
    browser->removeNode( item->iter() );
}

void BrowserModel::indexIter( const BrowserIter &iter,
    Browser &browser,
    NodeItem &item )
{
    ConnectionIndex *index;

    index = browserToConnectionMap[&browser];
    index->indexIter( iter, item );
}

void BrowserModel::removeIterIndex( const BrowserIter &iter,
    Browser &browser )
{
    ConnectionIndex *index;

    index = browserToConnectionMap[&browser];
    index->removeIter( iter );
}

NodeItem *BrowserModel::itemFromBrowserIter( const BrowserIter &iter,
    Browser &browser )
{
    ConnectionIndex *index;
    
    index = browserToConnectionMap[&browser];
    return index->itemFromIter( iter );
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
Browser *BrowserModel::createBrowser( CommunicationManager &commMgr,
    XmlConnection &connection )
{
    Browser *browser = new Browser( commMgr, connection, this );
    QList<NotePlugin*> pluginList = plugins();
    QList<NotePlugin*>::Iterator itr;
    for( itr = pluginList.begin(); itr != pluginList.end(); itr++ )
    {
        browser->addPlugin( **itr );
    }
    m_browsers.append( browser );
    emit( browserAdded( *browser ) );
    return browser;
}

}

