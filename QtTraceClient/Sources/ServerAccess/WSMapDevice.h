#ifndef WSMAPDEVICE_H
#define WSMAPDEVICE_H

#include "WebServiceRequest.h"


class CWSMapDevice : public CWebServiceRequest
{
    Q_OBJECT

public:
    CWSMapDevice();
    virtual ~CWSMapDevice();

    const int& deviceId() const         { return m_DeviceId; }
    int& deviceId()                     { return m_DeviceId; }

    const int& clientId() const         { return m_ClientId; }
    int& clientId()                     { return m_ClientId; }

    virtual void send();

public slots:

signals:

    void deviceMapped(int deviceId);

protected:

    virtual void onHandleResult(const QJsonDocument& doc);
    virtual void onHandleNetworkError();

protected:

    int             m_DeviceId;
    int             m_ClientId;
};


#endif // WSMAPDEVICE_H
