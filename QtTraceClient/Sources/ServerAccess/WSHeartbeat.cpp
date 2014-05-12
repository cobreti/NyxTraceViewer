#include "WSHeartbeat.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>



CWSHeartbeat::CWSHeartbeat() : CWebServiceRequest("/command/heartbeat")
{

}


CWSHeartbeat::~CWSHeartbeat()
{

}


void CWSHeartbeat::onHandleResult(const QJsonDocument &doc)
{
    QString result;
    QJsonObject obj = doc.object();
    QJsonObject::iterator it = obj.find("result");

    if ( it != obj.end() )
    {
        QJsonValue value = it.value();
        result = value.toString();
    }

    if ( result == "success" )
    {
        emit heartbeatSuccessfull();
    }
    else
    {
        emit heartbeatFailure();
    }
}


void CWSHeartbeat::onHandleNetworkError()
{
    emit heartbeatFailure();
}

