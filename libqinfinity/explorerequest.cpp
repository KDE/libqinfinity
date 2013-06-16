/*
 * Copyright 2013  Sven Brauch <svenbrauch@gmail.com>
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

#include "explorerequest.h"
#include "wrapperstore.h"
#include "qgsignal.h"

#include <QDebug>

#include "explorerequest.moc"

namespace QInfinity {

ExploreRequest::ExploreRequest(InfcExploreRequest* req, QObject* parent)
    : Request(INFC_REQUEST(req), parent)
{
    new QGSignal(this, "finished",
                 G_CALLBACK(ExploreRequest::finished_cb), this, this);
}

ExploreRequest* ExploreRequest::wrap(InfcExploreRequest* request, QObject* parent, bool own_gobject)
{
    QGObject* wrapptr = WrapperStore::getWrapper(G_OBJECT(request), own_gobject);
    if ( wrapptr ) {
        return qobject_cast<ExploreRequest*>(wrapptr);
    }
    ExploreRequest* wrapper = new ExploreRequest(request, parent);
    return wrapper;
}

void ExploreRequest::signalFinished()
{
    qDebug() << "emitting finished" << this;
    emit finished(this);
}

void ExploreRequest::finished_cb(InfcRequest* /*req*/, void* user_data)
{
    qDebug() << "node request finished" << user_data;
    static_cast<ExploreRequest*>(user_data)->signalFinished();
}

}
