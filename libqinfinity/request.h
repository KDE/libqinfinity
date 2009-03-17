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
        Request( InfcRequest *infRequest,
            QObject *parent = 0 );

    Q_SIGNALS:
        void failed( GError *error );
    
    private:
        void setupSignals();
        void signalFailed( GError *error );

        static void signalFailed_cb( InfcRequest *request,
            GError *error,
            void *user_data );

};

}

#endif

