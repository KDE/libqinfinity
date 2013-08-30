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

#ifndef QINFINITY_EXPLOREREQUEST_H
#define QINFINITY_EXPLOREREQUEST_H

#include "qgobject.h"
#include "request.h"
#include <libinfinity/common/inf-explore-request.h>

typedef struct _InfExploreRequest InfExploreRequest;
typedef struct _InfBrowserIter InfBrowserIter;

namespace QInfinity {

class ExploreRequest
    : public Request
{
Q_OBJECT
public:
    ExploreRequest(InfExploreRequest* req, QObject* parent = 0);
    static ExploreRequest* wrap(InfExploreRequest* request, QObject* parent = 0, bool own_gobject = false);

signals:
    void finished(ExploreRequest* self);

private:
    void signalFinished();
    static void finished_cb(InfExploreRequest* req, InfBrowserIter* iter, GError* error, void* user_data);
};

}

#endif
