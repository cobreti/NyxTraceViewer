#include "WSSetTraceClient.h"


#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


CWSSetTraceClient::CWSSetTraceClient() : CWebServiceRequest("/command/traceclient/set")
{

}


CWSSetTraceClient::~CWSSetTraceClient()
{

}


void CWSSetTraceClient::send()
{
    m_Parameters["name"] = m_Name;
    m_Parameters["address"] = m_HostAddress.toString();

    CWebServiceRequest::send();
}



void CWSSetTraceClient::onHandleResult(const QJsonDocument& doc)
{
    QString result;
    int id = -1;

    QJsonObject obj = doc.object();
    QJsonObject::iterator it = obj.find("result");

    if ( it != obj.end() )
    {
        QJsonValue value = it.value();
        result = value.toString();
    }

    it = obj.find("id");
    if ( it != obj.end() )
    {
        id = it.value().toInt();
    }


    if ( result == "success" && id > 0 )
    {
        emit registered(id);

        it = obj.find("mappings");
        if ( it != obj.end() )
        {
            QJsonArray mappings = it.value().toArray();
            extractMapping(mappings);
        }
    }
    else
    {
        emit registerFailure();
    }
}


void CWSSetTraceClient::onHandleNetworkError()
{
    emit registerFailure();
}


void CWSSetTraceClient::extractMapping(const QJsonArray &mappings)
{
    QJsonObject::iterator   pos;
    QJsonObject             value;

    int index = 0;
    while (index < mappings.count())
    {
        value = mappings[index].toObject();

        pos = value.find("id");
        QJsonValue idValue = pos.value();
        int id = idValue.toInt();

        pos = value.find("alias");
        QJsonValue aliasValue = pos.value();
        QString alias = aliasValue.toString();

        pos = value.find("name");
        QJsonValue nameValue = pos.value();
        QString name = nameValue.toString();

        emit clientMapping(id, alias, name);

        ++ index;
    }
}
