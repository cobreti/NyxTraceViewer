#ifndef WSUNMAPDEVICE_H
#define WSUNMAPDEVICE_H


#include "WebServiceRequest.h"


class CWSUnmapDevice : public CWebServiceRequest
{
    Q_OBJECT

public:

    CWSUnmapDevice();
    virtual ~CWSUnmapDevice();

    const int& deviceId() const         { return m_DeviceId; }
    int& deviceId()                     { return m_DeviceId; }

    virtual void send();

public slots:

signals:

    void deviceUnmapped(int deviceId);

protected:

    virtual void onHandleResult(const QJsonDocument &doc);
    virtual void onHandleNetworkError();

protected:

    int     m_DeviceId;
};


#endif // WSUNMAPDEVICE_H
