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

#include "noderequest.h"
#include "wrapperstore.h"
#include "qgsignal.h"

#include <QDebug>

#include "noderequest.moc"

namespace QInfinity {

NodeRequest::NodeRequest(InfNodeRequest* req, QObject* parent)
    : Request(INF_REQUEST(req), parent)
{
    new QGSignal(this, "finished",
                 G_CALLBACK(NodeRequest::finished_cb), this, this);
}

NodeRequest* NodeRequest::wrap(InfNodeRequest* request, QObject* parent, bool own_gobject)
{
    QGObject* wrapptr = WrapperStore::getWrapper(G_OBJECT(request), own_gobject);
    if ( wrapptr ) {
        return qobject_cast<NodeRequest*>(wrapptr);
    }
    NodeRequest* wrapper = new NodeRequest(request, parent);
    return wrapper;
}

void NodeRequest::signalFinished()
{
    qDebug() << "emitting finished" << this;
    emit finished(this);
}

void NodeRequest::finished_cb(InfNodeRequest* req, InfBrowserIter* iter, GError* error, void* user_data)
{
    qDebug() << "node request finished" << req << iter << error << user_data;
    static_cast<NodeRequest*>(user_data)->signalFinished();
}

}
