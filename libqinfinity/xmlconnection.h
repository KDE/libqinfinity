#ifndef QINFINITY_XMLCONNECTION_H
#define QINFINITY_XMLCONNECTION_H

#include <libinfinity/common/inf-xml-connection.h>

#include "qgobject.h"

#include <QObject>

namespace QInfinity
{

class XmlConnection
    : public QObject
    , public QGObject
{
    Q_OBJECT

    public:
        XmlConnection( InfXmlConnection *infXmlConnection,
            QObject *parent = 0 );

        void close();

    Q_SIGNALS:
        void error();

    private:
        void registerSignals();

        void signalError();

        static void error_cb( const GError *error,
            void *user_data );

};

}

#endif

