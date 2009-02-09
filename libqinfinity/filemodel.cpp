#include "filemodel.h"

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
    delete m_itemFactory;
}

}

