#ifndef WSGETDEVICES_H
#define WSGETDEVICES_H

#include "Device.h"
#include "WebServiceRequest.h"


class CWSGetDevices : public CWebServiceRequest
{
    Q_OBJECT

public:
    CWSGetDevices();
    virtual ~CWSGetDevices();

public slots:


signals:

    void devicesRefresh( const CDevice::IdMap& devicesMap );

protected:

    virtual void onHandleResult(const QJsonDocument& doc);
    virtual void onHandleNetworkError();

};

#endif // WSGETDEVICES_H
