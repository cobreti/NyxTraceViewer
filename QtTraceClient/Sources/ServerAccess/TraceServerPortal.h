#ifndef TRACESERVERPORTAL_H
#define TRACESERVERPORTAL_H

#include <QString>
#include <QNetworkInterface>
#include "Device.h"


#include <QObject>

class CWSSetTraceClient;
class CWSGetDevices;

class CTraceServerPortal : public QObject
{
    Q_OBJECT

public:
    CTraceServerPortal();
    virtual ~CTraceServerPortal();

    void setTraceClient(const QString& name);
    void setServer(const QString& server);
    void getDevices();

    QHostAddress GetHostAddress();

public slots:

    void onDevicesRefresh(const CDevice::IdMap& devicesList );

signals:

    void devicesRefresh( const CDevice::IdMap& devicesList );

protected:

protected:

    QString                 m_Name;
    QString                 m_Server;

    CWSSetTraceClient*      m_p_ws_SetTraceClient;
    CWSGetDevices*          m_p_ws_GetDevices;
};


#endif // TRACESERVERPORTAL_H
