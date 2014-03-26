#ifndef WSSETTRACECLIENT_H
#define WSSETTRACECLIENT_H


#include <QObject>
#include <QString>
#include <QNetworkInterface>
#include <QNetworkAccessManager>
#include <QScriptValue>

class QNetworkReply;


class CWSSetTraceClient : public QObject
{
    Q_OBJECT

public:
    CWSSetTraceClient();
    virtual ~CWSSetTraceClient();

    const QString&      server() const          { return m_Server; }
    QString&            server()                { return m_Server; }

    const QString&      name() const            { return m_Name; }
    QString&            name()                  { return m_Name; }

    const QHostAddress&     address() const     { return m_HostAddress; }
    QHostAddress&           address()           { return m_HostAddress; }

    void send();

public slots:

     void onResult(QNetworkReply*);

signals:

protected:

     void parseResult(QScriptValue value);

protected:

    QString                     m_Server;
    QString                     m_Name;
    QHostAddress                m_HostAddress;

    QNetworkAccessManager       m_NetworkManager;
    QNetworkReply*              m_pCurrentReply;
};

#endif // WSSETTRACECLIENT_H

