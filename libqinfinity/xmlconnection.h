/*
 * Copyright 2009  Gregory Haynes <greg@greghaynes.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
    Q_OBJECT;

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
        bool own_gobject = true );

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
        unsigned long error_handler;
        unsigned long status_handler;

};

}

#endif

