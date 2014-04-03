#ifndef WSGETDEVICES_H
#define WSGETDEVICES_H

#include "Device.h"

#include <QObject>
#include <QString>
#include <QNetworkInterface>
#include <QNetworkAccessManager>


class CWSGetDevices : public QObject
{
    Q_OBJECT

public:
    CWSGetDevices();
    virtual ~CWSGetDevices();

    const QString&      server() const          { return m_Server; }
    QString&            server()                { return m_Server; }

    void send();

public slots:

    void onResult(QNetworkReply*);

signals:

    void devicesRefresh( const CDevice::IdMap& devicesMap );

protected:

    QString         m_Server;

    QNetworkAccessManager       m_NetworkManager;
    QNetworkReply*              m_pCurrentReply;
};

#endif // WSGETDEVICES_H
