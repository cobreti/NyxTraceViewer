#ifndef CTEXTINPUTSERVER_H
#define CTEXTINPUTSERVER_H

#include <QObject>
#include <QTcpServer>

class CTextInputServer : public QObject
{
    Q_OBJECT
public:
    explicit CTextInputServer(QObject *parent = 0);

    virtual void Start();
    virtual void Stop();

signals:

public slots:

    void OnNewConnection();
    void OnNewData();

protected:

    QTcpServer      _server;
    QTcpSocket*     _pSocket;
};

#endif // CTEXTINPUTSERVER_H
