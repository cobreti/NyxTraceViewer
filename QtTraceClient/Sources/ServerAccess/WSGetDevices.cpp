#include "WSGetDevices.h"

#include <QUrlQuery>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


CWSGetDevices::CWSGetDevices() : CWebServiceRequest("/command/device/list")
{

}


CWSGetDevices::~CWSGetDevices()
{

}


void CWSGetDevices::onHandleResult(const QJsonDocument& doc)
{
    CDevice::IdMap       devicesMap;

    QJsonObject obj = doc.object();

    QJsonObject::iterator it = obj.find("result");
    QJsonValue value = it.value();
    QString result = value.toString();

    it = obj.find("devices");
    value = it.value();
    QString res = value.toString();
    if (value.isArray())
    {
        QJsonArray  devicesArray = value.toArray();
        int count = devicesArray.count();
        int index = 0;

        while ( index < count )
        {
            QJsonValue deviceEntry = devicesArray[index];
            if (deviceEntry.isObject())
            {
                QJsonObject deviceEntryObj = deviceEntry.toObject();
                CDevice device;

                it = deviceEntryObj.find("alias");
                value = it.value();
                device.alias() = value.toString();

                it = deviceEntryObj.find("name");
                value = it.value();
                device.name() = value.toString();

                it = deviceEntryObj.find("id");
                value = it.value();
                device.id() = value.toString().toInt();

                devicesMap[device.id()] = device;
            }
            ++ index;
        }

        emit devicesRefresh(devicesMap);

    }
}


void CWSGetDevices::onHandleNetworkError()
{

}

