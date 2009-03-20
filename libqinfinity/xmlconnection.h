#ifndef QINFINITY_XMLCONNECTION_H
#define QINFINITY_XMLCONNECTION_H

#include <libinfinity/common/inf-xml-connection.h>

#include "qgobject.h"

#include <QObject>
#include <QPointer>

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

    /**
     * @brief Returns wrapper XmlConnection 
     */
    static QPointer<XmlConnection> wrap( InfXmlConnection *infConnection,
        QObject *parent = 0,
        bool own_gobject = false );

        ~XmlConnection();
        QPointer<TcpConnection> tcpConnection();

        void close();
        Status status() const;

    protected:
        XmlConnection( InfXmlConnection *infXmlConnection,
            QObject *parent = 0,
            bool own_gobject = true );

    Q_SIGNALS:
        void statusChanged();
        void error( const GError *error );

    private:
        void registerSignals();

        void signalError( const GError *error );
        void signalStatusChanged();

        static void error_cb( InfXmlConnection *infConnection,
            const GError *error,
            void *user_data );
        static void status_changed_cb( InfXmlConnection *infConnection,
            const char *property,
            void *user_data );

        bool connected_to_error;

};

}

#endif

