#ifndef WEBSERVICEREQUEST_H
#define WEBSERVICEREQUEST_H

#include <QObject>
#include <QString>
#include <QNetworkInterface>
#include <QNetworkAccessManager>
#include <QJsonDocument>


class CWebServiceRequest : public QObject
{
    Q_OBJECT

public:
    CWebServiceRequest(const QString& method);
    virtual ~CWebServiceRequest();

    const QString&      server() const          { return m_Server; }
    QString&            server()                { return m_Server; }

    virtual void send();

public slots:

    void onResult(QNetworkReply*);

signals:


protected:

    virtual void onHandleResult(const QJsonDocument& doc) = 0;
    virtual void onHandleNetworkError() = 0;

protected:

    QString                     m_Server;
    QString                     m_Method;
    QString                     m_Key;

    QMap<QString, QVariant>     m_Parameters;

    QNetworkAccessManager       m_NetworkManager;
    QNetworkReply*              m_pCurrentReply;
};


#endif // WEBSERVICEREQUEST_H
