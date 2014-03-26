#ifndef TRACESERVERPORTAL_H
#define TRACESERVERPORTAL_H

#include <QString>
#include <QNetworkInterface>


class CWSSetTraceClient;

class CTraceServerPortal
{
public:
    CTraceServerPortal();
    virtual ~CTraceServerPortal();

    void setTraceClient(const QString& name);
    void setServer(const QString& server);

    QHostAddress GetHostAddress();

protected:

protected:

    QString                 m_Name;
    QString                 m_Server;

    CWSSetTraceClient*      m_p_ws_SetTraceClient;
};


#endif // TRACESERVERPORTAL_H
