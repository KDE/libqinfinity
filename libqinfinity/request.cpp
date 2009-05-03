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

#include "request.h"

#include "request.moc"

namespace QInfinity
{

Request::Request( InfcRequest *infRequest,
    QObject *parent )
    : QGObject( G_OBJECT( infRequest ), parent )
{
    setupSignals();
}

Request::~Request()
{
    g_signal_handler_disconnect( gobject(),
        failed_handler );
}

void Request::setupSignals()
{
    failed_handler = g_signal_connect( gobject(), "failed",
        G_CALLBACK(Request::signalFailed_cb), this );
}

void Request::signalFailed( GError *error )
{
    emit( failed( error ) );
}

void Request::signalFailed_cb( InfcRequest *request,
    GError *error,
    void *user_data )
{
    Request *sender = static_cast<Request*>(user_data);
    sender->signalFailed( error );
}

}

