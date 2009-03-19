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

