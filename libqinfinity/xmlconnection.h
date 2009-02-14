#ifndef QINFINITY_XMLCONNECTION_H
#define QINFINITY_XMLCONNECTION_H

#include <libinfinity/common/inf-xml-connection.h>

#include "qgobject.h"

#include <QObject>

namespace QInfinity
{

class TcpConnection;

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
        TcpConnection *tcpConnection();

        void close();
        Status status() const;

    Q_SIGNALS:
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

        bool connected_to_error;

};

}

#endif

