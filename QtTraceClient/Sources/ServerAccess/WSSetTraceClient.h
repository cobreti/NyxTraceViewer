#ifndef WSSETTRACECLIENT_H
#define WSSETTRACECLIENT_H


#include "WebServiceRequest.h"

class QNetworkReply;


class CWSSetTraceClient : public CWebServiceRequest
{
    Q_OBJECT

public:
    CWSSetTraceClient();
    virtual ~CWSSetTraceClient();

    const QString&      name() const            { return m_Name; }
    QString&            name()                  { return m_Name; }

    const QHostAddress&     address() const     { return m_HostAddress; }
    QHostAddress&           address()           { return m_HostAddress; }

    virtual void send();

public slots:

signals:

    void registered(int id);

protected:

    virtual void onHandleResult(const QJsonDocument& doc);

protected:

    QString                     m_Name;
    QHostAddress                m_HostAddress;
};

#endif // WSSETTRACECLIENT_H

