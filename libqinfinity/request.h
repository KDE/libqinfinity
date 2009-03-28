#ifndef QINFINITY_REQUEST_H
#define QINFINITY_REQUEST_H

#include "qgobject.h"

#include <libinfinity/client/infc-request.h>

#include <glib/gerror.h>

namespace QInfinity
{

class Request
    : public QGObject
{
    Q_OBJECT;

    public:
        // TODO: This should really use a wrap method
        Request( InfcRequest *infRequest,
            QObject *parent = 0 );
        ~Request();

    Q_SIGNALS:
        void failed( GError *error );
    
    private:
        void setupSignals();
        void signalFailed( GError *error );

        static void signalFailed_cb( InfcRequest *request,
            GError *error,
            void *user_data );

        unsigned long failed_handler;

};

}

#endif

