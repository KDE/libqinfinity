#include "certificatecredentials.h"

#include <libinfinity/common/inf-certificate-credentials.h>

namespace QInfinity
{

CertificateCredentials::CertificateCredentials( QObject *parent )
    : QGObject( parent )
{
    InfCertificateCredentials *cred = inf_certificate_credentials_new();
    setGobject((GObject*)cred);
}

CertificateCredentials::~CertificateCredentials()
{
    InfCertificateCredentials *cred;
    cred = (InfCertificateCredentials*)gobject();
    inf_certificate_credentials_unref(cred);
}

}

