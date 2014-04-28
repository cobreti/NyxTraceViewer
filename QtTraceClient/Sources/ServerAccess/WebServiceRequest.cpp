#include "WebServiceRequest.h"

#include <QUrlQuery>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>



CWebServiceRequest::CWebServiceRequest(const QString& method) : QObject(),
    m_Key("a35830b6-4060-4c3b-abd0-c24d079cdcd5"),
    m_Method(method),
    m_pCurrentReply(NULL)
{

}


CWebServiceRequest::~CWebServiceRequest()
{

}



void CWebServiceRequest::send()
{
    if ( m_Server.isEmpty() )
        return;

    m_Parameters["key"] = m_Key;

    QUrl url(m_Server);

    url.setPath( QString("%1%2").arg(url.path()).arg(m_Method));

    QUrlQuery   query;
    foreach(QString param, m_Parameters.keys())
    {
        query.addQueryItem(param, m_Parameters[param].toString());
    }


    QNetworkRequest request;
    request.setUrl(url);

    QByteArray      data;
    data.append(query.toString());

    connect( &m_NetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResult(QNetworkReply*)));

    m_pCurrentReply = m_NetworkManager.post(request, data);
}


void CWebServiceRequest::onResult(QNetworkReply* reply)
{
    if (m_pCurrentReply->error() != QNetworkReply::NoError)
    {
        onHandleNetworkError();
        return;
    }

    QByteArray data = reply->readAll();
    if (data.length() > 0)
    {
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(data, &err);

        onHandleResult(doc);
    }
}

