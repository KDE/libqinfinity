#ifndef QINFINITY_FILE_MODEL_H
#define QINFINITY_FILE_MODEL_H

#include "xmlconnection.h"
#include "fileitemfactory.h"

#include <QString>
#include <QList>
#include <QStandardItemModel>
#include <QMap>

namespace QInfinity
{

class Browser;

/**
 * @brief A model for connections and their file hierarchy
 */
class FileModel
    : public QStandardItemModel
{

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
        const QList<XmlConnection*> connections;

    private:
        FileItemFactory *m_itemFactory;
        QList<XmlConnection*> m_connections;
        QMap<Browser*, XmlConnection*> browserToConnectionMap;

};

}

#endif

