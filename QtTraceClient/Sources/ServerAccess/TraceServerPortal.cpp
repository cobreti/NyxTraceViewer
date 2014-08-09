
#include "TraceServerPortal.h"
#include "WSSetTraceClient.h"
#include "WSGetDevices.h"
#include "WSMapDevice.h"
#include "WSUnmapDevice.h"
#include "WSHeartbeat.h"

#include <QHostInfo>


CTraceServerPortal::CTraceServerPortal() : QObject(),
    m_p_ws_SetTraceClient(new CWSSetTraceClient()),
    m_p_ws_GetDevices(new CWSGetDevices()),
    m_p_ws_MapDevice(new CWSMapDevice()),
    m_p_ws_UnmapDevice(new CWSUnmapDevice()),
    m_p_ws_Heartbeat(new CWSHeartbeat())
{
    connect(    m_p_ws_GetDevices, SIGNAL(devicesRefresh(CDevice::IdMap)),
                this, SLOT(onDevicesRefresh(CDevice::IdMap)) );
    connect(    m_p_ws_MapDevice, SIGNAL(deviceMapped(int)),
                this, SLOT(onDeviceMapped(int)) );
    connect(    m_p_ws_UnmapDevice, SIGNAL(deviceUnmapped(int)),
                this, SLOT(onDeviceUnmapped(int)) );
    connect(    m_p_ws_SetTraceClient, SIGNAL(registered(int)),
                this, SLOT(onClientRegistered(int)));
    connect(    m_p_ws_SetTraceClient, SIGNAL(clientMapping(int,QString,QString)),
                this, SLOT(onClientMapping(int,QString,QString)) );
    connect(    m_p_ws_SetTraceClient, SIGNAL(registerFailure()),
                this, SLOT(onClientRegisterFailed()));
    connect(    m_p_ws_Heartbeat, SIGNAL(heartbeatSuccessfull()),
                this, SLOT(onHeartbeatSuccessfull()) );
    connect(    m_p_ws_Heartbeat, SIGNAL(heartbeatFailure()),
                this, SLOT(onHeartbeatFailure()) );
}


CTraceServerPortal::~CTraceServerPortal()
{
    delete m_p_ws_UnmapDevice;
    delete m_p_ws_MapDevice;
    delete m_p_ws_GetDevices;
    delete m_p_ws_SetTraceClient;
    delete m_p_ws_Heartbeat;
}


void CTraceServerPortal::setTraceClient(const QString& name)
{
    m_Name = name;

    QHostAddress            hostAddress = GetHostAddress();

    m_p_ws_SetTraceClient->server() = m_Server;
    m_p_ws_SetTraceClient->name() = m_Name;
    m_p_ws_SetTraceClient->address() = hostAddress.toString();

    m_p_ws_SetTraceClient->send();
}


void CTraceServerPortal::setServer(const QString &server)
{
    m_Server = server;

    QRegExp         exp("http://(.*)");

    if ( !exp.exactMatch(m_Server) )
    {
        m_Server = QString("%1%2").arg("http://").arg(m_Server);
    }
}


void CTraceServerPortal::getDevices()
{
    m_p_ws_GetDevices->server() = m_Server;
    m_p_ws_GetDevices->send();
}


void CTraceServerPortal::setClientMapping(int deviceId, int clientId)
{
    m_p_ws_MapDevice->server() = m_Server;
    m_p_ws_MapDevice->deviceId() = deviceId;
    m_p_ws_MapDevice->clientId() = clientId;
    m_p_ws_MapDevice->send();
}


void CTraceServerPortal::removeClientMapping(int deviceId)
{
    m_p_ws_UnmapDevice->server() = m_Server;
    m_p_ws_UnmapDevice->deviceId() = deviceId;
    m_p_ws_UnmapDevice->send();
}


void CTraceServerPortal::checkServerConnection()
{
    m_p_ws_Heartbeat->server() = m_Server;
    m_p_ws_Heartbeat->send();
}


QHostAddress CTraceServerPortal::GetHostAddress()
{
    QHostInfo info = QHostInfo::fromName( QHostInfo::localHostName() );


    QList<QHostAddress>     list = info.addresses();
    QHostAddress            hostAddress;
    QString                 addr;

    for (int index = 0; index < list.count(); ++index)
    {
        addr = list[index].toString();
        if ( !list[index].isLoopback() && list[index].protocol() == QAbstractSocket::IPv4Protocol )
        {
            hostAddress = list[index];
            break;
        }
    }

    return hostAddress;
}


void CTraceServerPortal::onDevicesRefresh(const CDevice::IdMap &devicesList)
{
    emit devicesRefresh(devicesList);
}


void CTraceServerPortal::onClientRegistered(int id)
{
    emit clientRegistered(id);
}


void CTraceServerPortal::onClientRegisterFailed()
{
    emit clientRegisterFailed();
}


void CTraceServerPortal::onDeviceMapped(int id)
{
    emit deviceMapped(id);
}


void CTraceServerPortal::onDeviceUnmapped(int id)
{
    emit deviceUnmapped(id);
}


void CTraceServerPortal::onClientMapping(int id, const QString &alias, const QString &name)
{
    emit clientMapping(id, alias, name);
}


void CTraceServerPortal::onHeartbeatSuccessfull()
{
    emit heartbeatSuccessfull();
}


void CTraceServerPortal::onHeartbeatFailure()
{
    emit heartbeatFailure();
}

