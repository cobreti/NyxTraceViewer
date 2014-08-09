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
class CWSHeartbeat;

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
    void checkServerConnection();

    const QString& server() const   { return m_Server; }
    QString& server()               { return m_Server; }

    const QString& traceClientName() const  { return m_Name; }
    QString& traceClientName()              { return m_Name; }

    QHostAddress GetHostAddress();

public slots:

    void onDevicesRefresh(const CDevice::IdMap& devicesList );
    void onClientRegistered(int id);
    void onClientRegisterFailed();
    void onDeviceMapped(int id);
    void onDeviceUnmapped(int id);
    void onClientMapping(int id, const QString& alias, const QString& name);
    void onHeartbeatSuccessfull();
    void onHeartbeatFailure();

signals:

    void devicesRefresh( const CDevice::IdMap& devicesList );
    void clientRegistered(int id);
    void clientRegisterFailed();
    void deviceMapped(int id);
    void deviceUnmapped(int id);
    void clientMapping(int id, const QString& alias, const QString& name);
    void heartbeatSuccessfull();
    void heartbeatFailure();

protected:

protected:

    QString                 m_Name;
    QString                 m_Server;

    CWSSetTraceClient*      m_p_ws_SetTraceClient;
    CWSGetDevices*          m_p_ws_GetDevices;
    CWSMapDevice*           m_p_ws_MapDevice;
    CWSUnmapDevice*         m_p_ws_UnmapDevice;
    CWSHeartbeat*           m_p_ws_Heartbeat;
};


#endif // TRACESERVERPORTAL_H
