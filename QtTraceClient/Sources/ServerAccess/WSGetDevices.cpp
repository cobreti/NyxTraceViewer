#include "WSGetDevices.h"

#include <QUrlQuery>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


CWSGetDevices::CWSGetDevices() : QObject()
{

}


CWSGetDevices::~CWSGetDevices()
{

}


void CWSGetDevices::send()
{
    if ( m_Server.isEmpty() )
        return;

    QUrl url(m_Server);
    QString method = "/command/device/list";

    url.setPath( QString("%1%2").arg(url.path()).arg(method));

    QMap<QString, QVariant> params;
//    params["name"] = m_Name;
//    params["address"] = m_HostAddress.toString();

    QUrlQuery   query;
    foreach(QString param, params.keys())
    {
        query.addQueryItem(param, params[param].toString());
    }

    QNetworkRequest request;
    request.setUrl(url);

    QString urlstr = url.toString();

    QByteArray      data;
    data.append(query.toString());

    connect( &m_NetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResult(QNetworkReply*)));

    m_pCurrentReply = m_NetworkManager.post(request, data);
}


void CWSGetDevices::onResult(QNetworkReply* reply)
{
    if (m_pCurrentReply->error() != QNetworkReply::NoError)
        return;

    CDevice::IdMap       devicesMap;

    QByteArray data = reply->readAll();
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);

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

