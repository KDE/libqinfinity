#include "browsermodel.h"
#include "browser.h"
#include "xmlconnection.h"
#include "browseritemfactory.h"

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

BrowserModel::BrowserModel( QObject *parent )
    : QStandardItemModel( parent )
    , m_itemFactory( new BrowserItemFactory )
{
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

BrowserModel::BrowserModel( QList<XmlConnection*> connections,
    QObject *parent )
    : QStandardItemModel( parent )
    , m_itemFactory( new BrowserItemFactory )
    , m_connections( connections )
{
}

BrowserModel::BrowserModel( BrowserItemFactory *itemFactory,
    QList<XmlConnection*> connections,
    QObject *parent )
    : QStandardItemModel( parent )
    , m_itemFactory( itemFactory )
    , m_connections( connections )
{
    if( !m_itemFactory )
        m_itemFactory = new BrowserItemFactory;
    m_itemFactory->setParent( this );
}

BrowserModel::~BrowserModel()
{
    QList<Browser*> browsers;
    QList<Browser*>::Iterator browserItr;
    QList<ConnectionIndex*> connIdexes;
    QList<ConnectionIndex*>::Iterator connIndexItr;
    
    browsers = browserToConnectionMap.keys();
    for( browserItr = browsers.begin(); browserItr != browsers.end(); browserItr++ )
        delete *browserItr;

    connIdexes = browserToConnectionMap.values();
    for( connIndexItr = connIdexes.begin(); connIndexItr != connIdexes.end(); connIndexItr++ )
        delete *connIndexItr;
    
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

    browser = new Browser( comm_mgr, connection, this );
    index = new ConnectionIndex( connection, *browser );

    browserToConnectionMap[browser] = index;
    connect( browser, SIGNAL(nodeAdded( const BrowserIter&)),
        this, SLOT(slotNodeAdded( const BrowserIter&)) );

    connItem = m_itemFactory->createConnectionItem( connection,
        name );
    insertRow( 0, connItem );
    BrowserIter rootNode( *browser );
    nodeItem = m_itemFactory->createRootNodeItem( rootNode );
    indexIter( rootNode, *browser, *nodeItem );
    connItem->setChild( 0, nodeItem );
    return connItem;
}

const QList<XmlConnection*> BrowserModel::connections() const
{
    return m_connections;
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

void BrowserModel::indexIter( const BrowserIter &iter,
    Browser &browser,
    NodeItem &item )
{
    ConnectionIndex *index;

    index = browserToConnectionMap[&browser];
    index->indexIter( iter, item );
}

NodeItem *BrowserModel::itemFromBrowserIter( const BrowserIter &iter,
    Browser &browser )
{
    ConnectionIndex *index;
    
    index = browserToConnectionMap[&browser];
    return index->itemFromIter( iter );
}

NodeItem *BrowserModel::indexToNodeItem( const QModelIndex &parent ) const
{
    if( !parent.isValid() )
        return 0;
    QStandardItem *stdItem = static_cast<QStandardItem*>(parent.internalPointer());
    if( stdItem->type() == BrowserItemFactory::NodeItem )
        return dynamic_cast<NodeItem*>(stdItem);
    else
        return 0;
}

}

