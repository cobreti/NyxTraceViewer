#include "WSMapDevice.h"

#include <QJsonDocument>
#include <QJsonObject>


CWSMapDevice::CWSMapDevice() : CWebServiceRequest("/command/mapping/set"),
    m_DeviceId(-1),
    m_ClientId(-1)
{

}


CWSMapDevice::~CWSMapDevice()
{

}


void CWSMapDevice::send()
{
    m_Parameters["deviceId"] = QString::number(m_DeviceId);
    m_Parameters["clientId"] = QString::number(m_ClientId);

    CWebServiceRequest::send();
}


void CWSMapDevice::onHandleResult(const QJsonDocument& doc)
{
    QJsonObject obj = doc.object();
    QJsonObject::iterator it = obj.find("result");
    QJsonValue value = it.value();
    QString result = value.toString();

    if ( result == "success" )
    {
        emit deviceMapped(m_DeviceId);
    }
}


void CWSMapDevice::onHandleNetworkError()
{

}
