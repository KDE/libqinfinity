#ifndef QINFINITY_FILE_ITEM_FACTORY
#define QINFINITY_FILE_ITEM_FACTORY

#include <QObject>
#include <QIcon>
#include <QStandardItem>

#include "browseriter.h"

namespace QInfinity
{

class BrowserIter;
class XmlConnection;

/**
 * @brief Convinience QStandardItem class for representing a BrowserIter
 */
class NodeItem
    : public QStandardItem
{

    public:
        /**
         * @brief Create item with iter.name() as text.
         */
        NodeItem( const BrowserIter &iter );
        NodeItem( const BrowserIter &iter,
            const QString &text );
        NodeItem( const BrowserIter &iter,
            const QIcon &icon );
        NodeItem( const BrowserIter &iter,
            const QIcon &icon,
            const QString &text );

        const BrowserIter &iter() const;

    private:
        BrowserIter m_iter;

};

class ConnectionItem
    : public QStandardItem
{
    public:
        ConnectionItem( XmlConnection &connection,
            const QString &text );
        ConnectionItem( XmlConnection &connection,
            const QIcon &icon,
            const QString &text );

        XmlConnection &connection() const;

    private:
        XmlConnection *m_connection;
        
};

class FileItemFactory
    : public QObject
{

    public:
        FileItemFactory( QObject *parent = 0);
        virtual ~FileItemFactory();

        virtual QStandardItem *newDirectoryItem( const BrowserIter &node );
        virtual QStandardItem *newNoteItem( const BrowserIter &node );
        virtual QStandardItem *newConnectionItem( XmlConnection &connection,
            const QString &name );

};

}

#endif

