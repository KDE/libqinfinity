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

#ifndef QINFINITY_NODEREQUEST_H
#define QINFINITY_NODEREQUEST_H

#include "qgobject.h"
#include "request.h"
#include <libinfinity/client/infc-node-request.h>

typedef struct _InfcNodeRequest InfcNodeRequest;

namespace QInfinity {

class NodeRequest
    : public Request
{
Q_OBJECT
public:
    NodeRequest(InfcNodeRequest* req, QObject* parent = 0);
    static NodeRequest* wrap(InfcNodeRequest* request, QObject* parent = 0, bool own_gobject = true);

signals:
    void finished(NodeRequest* self);

private:
    void signalFinished();
    static void finished_cb(InfcRequest* req, InfcBrowserIter* iter, void* user_data);
};

}

#endif
