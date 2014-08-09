#include "WSUnmapDevice.h"

#include <QJsonDocument>
#include <QJsonObject>


CWSUnmapDevice::CWSUnmapDevice() : CWebServiceRequest("/command/mapping/unset"),
    m_DeviceId(-1)
{

}


CWSUnmapDevice::~CWSUnmapDevice()
{

}

void CWSUnmapDevice::send()
{
    m_Parameters["deviceId"] = QString::number(m_DeviceId);

    CWebServiceRequest::send();
}


void CWSUnmapDevice::onHandleResult(const QJsonDocument& doc)
{
    QJsonObject obj = doc.object();
    QJsonObject::iterator it = obj.find("result");
    QJsonValue value = it.value();
    QString result = value.toString();

    if ( result == "success" )
    {
        emit deviceUnmapped(m_DeviceId);
    }
}


void CWSUnmapDevice::onHandleNetworkError()
{

}


