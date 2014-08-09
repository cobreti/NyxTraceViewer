#ifndef WSSETTRACECLIENT_H
#define WSSETTRACECLIENT_H


#include "WebServiceRequest.h"


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
    void registerFailure();
    void clientMapping(int id, const QString& alias, const QString& name);

protected:

    virtual void onHandleResult(const QJsonDocument& doc);
    virtual void onHandleNetworkError();
    virtual void extractMapping(const QJsonArray& mappings);

protected:

    QString                     m_Name;
    QHostAddress                m_HostAddress;
};

#endif // WSSETTRACECLIENT_H

