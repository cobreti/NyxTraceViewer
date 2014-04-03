
#include "TraceServerPortal.h"
#include "WSSetTraceClient.h"
#include "WSGetDevices.h"



CTraceServerPortal::CTraceServerPortal() : QObject(),
    m_p_ws_SetTraceClient(new CWSSetTraceClient()),
    m_p_ws_GetDevices(new CWSGetDevices())
{
    connect(    m_p_ws_GetDevices, SIGNAL(devicesRefresh(CDevice::IdMap)),
                this, SLOT(onDevicesRefresh(CDevice::IdMap)) );
}


CTraceServerPortal::~CTraceServerPortal()
{

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


QHostAddress CTraceServerPortal::GetHostAddress()
{
    QList<QHostAddress>     list = QNetworkInterface::allAddresses();
    QHostAddress            hostAddress;

    for (int index = 0; index < list.count(); ++index)
    {
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
