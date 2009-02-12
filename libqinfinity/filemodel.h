#ifndef QINFINITY_FILE_MODEL_H
#define QINFINITY_FILE_MODEL_H

#include "xmlconnection.h"
#include "fileitemfactory.h"
#include "communicationmanager.h"

#include <QString>
#include <QList>
#include <QStandardItemModel>
#include <QMap>
#include <QPointer>

namespace QInfinity
{

class Browser;

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
class FileModel
    : public QStandardItemModel
{
    Q_OBJECT

    public:
        FileModel( QObject *parent = 0 );
        FileModel( FileItemFactory *itemFactory,
            QObject *parent = 0 );
        FileModel( QList<XmlConnection*> connections,
            QObject *parent = 0 );
        FileModel( FileItemFactory *itemFactory,
            QList<XmlConnection*> connections,
            QObject *parent = 0 );
        ~FileModel();

        /**
         * @brief Use factory for creating items.
         *
         * If factory is NULL then FileItemFactory is used.
         * factory will be reparented.
         */
        void setFileItemFactory( FileItemFactory *factory );
        FileItemFactory &itemFactory() const;
        /**
         * @brief Add connection with name for model to represent.
         */
        void addConnection( XmlConnection &connection,
            const QString &name );
        const QList<XmlConnection*> connections() const;

    private Q_SLOTS:
        void slotNodeAdded( const BrowserIter &itr );

    private:
        void indexIter( const BrowserIter &iter,
            Browser &browser,
            NodeItem &item );
        NodeItem *itemFromBrowserIter( const BrowserIter &iter,
            Browser &browser );

        FileItemFactory *m_itemFactory;
        QList<XmlConnection*> m_connections;
        QMap<Browser*, ConnectionIndex*> browserToConnectionMap;
        CommunicationManager comm_mgr;

};

}

#endif

