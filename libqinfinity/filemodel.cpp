#include "filemodel.h"
#include "browser.h"

namespace QInfinity
{

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
    
    browsers = browserToConnectionMap.keys();
    for( browserItr = browsers.begin(); browserItr != browsers.end(); browserItr++ )
        delete *browserItr;
    
    delete m_itemFactory;
}

}

