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

#ifndef QINFINITY_EXPLORE_REQUEST_H
#define QINFINITY_EXPLORE_REQUEST_H

#include "request.h"

#include <libinfinity/client/infc-explore-request.h>

namespace QInfinity
{

class ExploreRequest
    : public Request
{
    Q_OBJECT;

    public:
        ExploreRequest( InfcExploreRequest *infRequest,
            QObject *parent = 0 );

        unsigned int nodeId();

        /**
         * @brief Cause emission of progress signal.
         */
        bool emitProgress( GError **error );

        bool isInitiated();
        bool isFinished();
    
    Q_SIGNALS:
        void finished();
        void initiated( unsigned int nodes );
        void progress( unsigned int nodes,
            unsigned int total );

    private:
        void setupSignals();

};

}

#endif

