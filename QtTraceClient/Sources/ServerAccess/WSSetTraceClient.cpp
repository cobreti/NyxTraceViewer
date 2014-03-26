#include "WSSetTraceClient.h"


#include <QUrlQuery>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QScriptEngine>
#include <QScriptValueIterator>
#include <QScopedPointer>

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
//    url.setQuery(query);

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

    QString data = reply->readAll();
    data = data.replace("\n", "");

    QScriptEngine engine;
    QScriptValue dataVal = engine.evaluate("(" + data + ")");

    parseResult(dataVal);
//    QScriptValueIterator        it(dataVal);
//    QString name;

//    while (it.hasNext())
//    {
//        it.next();
//        QScriptValue val = it.value();
//        name = it.name();
//    }
}


void CWSSetTraceClient::parseResult(QScriptValue value)
{
    QString     text;

    if ( value.isArray() || value.isObject() )
    {
        QScriptValueIterator        it(value);
        QString name;

        while (it.hasNext())
        {
            it.next();
            parseResult(it.value());
        }
    }
    else
    {
        text = value.toString();
    }
}
