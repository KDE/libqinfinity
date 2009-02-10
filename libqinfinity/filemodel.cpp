#include "filemodel.h"
#include "browser.h"

#include <QStack>

#include "filemodel.moc"

namespace QInfinity
{

ConnectionIndex::ConnectionIndex( XmlConnection &connection,
    Browser &browser )
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

NodeItem *ConnectionIndex::getNodeFromIter( const BrowserIter &iter ) const
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

FileModel::FileModel( QObject *parent )
    : QStandardItemModel( parent )
    , m_itemFactory( new FileItemFactory )
{
}

FileModel::FileModel( FileItemFactory *itemFactory,
    QObject *parent )
    : QStandardItemModel( parent )
    , m_itemFactory( itemFactory )
{
    if( !m_itemFactory)
        m_itemFactory = new FileItemFactory;
    m_itemFactory->setParent( this );
}

FileModel::FileModel( QList<XmlConnection*> connections,
    QObject *parent )
    : QStandardItemModel( parent )
    , m_itemFactory( new FileItemFactory )
    , m_connections( connections )
{
}

FileModel::FileModel( FileItemFactory *itemFactory,
    QList<XmlConnection*> connections,
    QObject *parent )
    : QStandardItemModel( parent )
    , m_itemFactory( itemFactory )
    , m_connections( connections )
{
    if( !m_itemFactory )
        m_itemFactory = new FileItemFactory;
    m_itemFactory->setParent( this );
}

FileModel::~FileModel()
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

void FileModel::addConnection( XmlConnection &connection,
    const QString &name )
{
    ConnectionIndex *index;
    Browser *browser = new Browser( comm_mgr, connection, this );
    index = new ConnectionIndex( connection, *browser );
    browserToConnectionMap[browser] = index;
    connect( browser, SIGNAL(nodeAdded(QPointer<BrowserIter>)),
        this, SLOT(slotNodeAdded(QPointer<BrowserIter>)) );
}

const QList<XmlConnection*> FileModel::connections() const
{
    return m_connections;
}

void FileModel::slotNodeAdded( QPointer<BrowserIter> itr )
{
}

}

