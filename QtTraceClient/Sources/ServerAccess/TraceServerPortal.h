#ifndef TRACESERVERPORTAL_H
#define TRACESERVERPORTAL_H

#include <QString>
#include <QNetworkInterface>
#include "Device.h"


#include <QObject>

class CWSSetTraceClient;
class CWSGetDevices;
class CWSMapDevice;
class CWSUnmapDevice;

class CTraceServerPortal : public QObject
{
    Q_OBJECT

public:
    CTraceServerPortal();
    virtual ~CTraceServerPortal();

    void setTraceClient(const QString& name);
    void setServer(const QString& server);
    void getDevices();
    void setClientMapping(int deviceId, int clientId);
    void removeClientMapping(int deviceId);

    QHostAddress GetHostAddress();

public slots:

    void onDevicesRefresh(const CDevice::IdMap& devicesList );
    void onClientRegistered(int id);
    void onDeviceMapped(int id);
    void onDeviceUnmapped(int id);

signals:

    void devicesRefresh( const CDevice::IdMap& devicesList );
    void clientRegistered(int id);
    void deviceMapped(int id);
    void deviceUnmapped(int id);

protected:

protected:

    QString                 m_Name;
    QString                 m_Server;

    CWSSetTraceClient*      m_p_ws_SetTraceClient;
    CWSGetDevices*          m_p_ws_GetDevices;
    CWSMapDevice*           m_p_ws_MapDevice;
    CWSUnmapDevice*         m_p_ws_UnmapDevice;
};


#endif // TRACESERVERPORTAL_H
