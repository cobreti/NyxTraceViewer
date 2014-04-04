#include "WSSetTraceClient.h"


#include <QJsonDocument>
#include <QJsonObject>


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
    QJsonObject obj = doc.object();
    QJsonObject::iterator it = obj.find("result");
    QJsonValue value = it.value();
    QString result = value.toString();
}
