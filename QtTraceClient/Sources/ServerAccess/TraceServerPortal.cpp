
#include "TraceServerPortal.h"
#include "WSSetTraceClient.h"



CTraceServerPortal::CTraceServerPortal() :
    m_p_ws_SetTraceClient(new CWSSetTraceClient())
{

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
//    CWSSetTraceClient       setTraceClient(m_Server, m_Name, hostAddress);

//    setTraceClient.send();
}


void CTraceServerPortal::setServer(const QString &server)
{
    m_Server = server;
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
