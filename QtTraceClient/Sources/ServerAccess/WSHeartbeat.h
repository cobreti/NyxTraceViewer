#ifndef WSHEARTBEAT_H
#define WSHEARTBEAT_H

#include "WebServiceRequest.h"


class CWSHeartbeat : public CWebServiceRequest
{
    Q_OBJECT

public:
    CWSHeartbeat();
    virtual ~CWSHeartbeat();

signals:

    void heartbeatSuccessfull();
    void heartbeatFailure();

protected:

    virtual void onHandleResult(const QJsonDocument &doc);
    virtual void onHandleNetworkError();
};

#endif // WSHEARTBEAT_H
