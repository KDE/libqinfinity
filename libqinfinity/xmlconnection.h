#ifndef QINFINITY_XMLCONNECTION_H
#define QINFINITY_XMLCONNECTION_H

#include <libinfinity/common/inf-xml-connection.h>

#include "qgobject.h"

#include <QObject>

namespace QInfinity
{

class XmlConnection
    : public QGObject
{
    Q_OBJECT

    public:
        enum Status
        {
            Closed,
            Closing,
            Open,
            Opening
        };

        static XmlConnection *create( InfXmlConnection *infConnection,
            QObject *parent = 0 );

        XmlConnection( InfXmlConnection *infXmlConnection,
            QObject *parent = 0 );

        void close();
        Status status() const;

    Q_SIGNALS:
        void error( const QString &message );
        void statusChanged();

    private:
        void registerSignals();

        void signalError( const GError *error );
        void signalStatusChanged();

        static void error_cb( const GError *error,
            void *user_data );
        static void status_changed_cb( InfXmlConnection *infConnection,
            const char *property,
            void *user_data );

};

}

#endif

