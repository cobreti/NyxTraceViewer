#include "WSSetTraceClient.h"


#include <QUrlQuery>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>


CWSSetTraceClient::CWSSetTraceClient() : QObject()
{

}


CWSSetTraceClient::~CWSSetTraceClient()
{

}


void CWSSetTraceClient::send()
{
    if ( m_Server.isEmpty() )
        return;

    QUrl url(m_Server);
    QString method = "/command/traceclient/set";

    url.setPath( QString("%1%2").arg(url.path()).arg(method));

    QMap<QString, QVariant> params;
    params["name"] = m_Name;
    params["address"] = m_HostAddress.toString();

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



void CWSSetTraceClient::onResult(QNetworkReply *reply)
{
    if (m_pCurrentReply->error() != QNetworkReply::NoError)
        return;

    QByteArray data = reply->readAll();
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);

    QJsonObject obj = doc.object();
    QJsonObject::iterator it = obj.find("result");
    QJsonValue value = it.value();
    QString result = value.toString();
}
