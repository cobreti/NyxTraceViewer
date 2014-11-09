#include "TextInputServer.h"

#include <memory>
#include <QTcpSocket>

CTextInputServer::CTextInputServer(QObject *parent) :
    QObject(parent),
    _pSocket(NULL)
{
    connect(    &_server, SIGNAL(newConnection()),
                this, SLOT(OnNewConnection()) );
}


void CTextInputServer::Start()
{
    _server.listen(QHostAddress::Any, 8501);
}


void CTextInputServer::Stop()
{

}


void CTextInputServer::OnNewConnection()
{
    _pSocket = _server.nextPendingConnection();

    connect(_pSocket, SIGNAL(readyRead()), this, SLOT(OnNewData()));
}


void CTextInputServer::OnNewData()
{
    const quint32 kBuffSize = 2048;
    char* pBuffer = new char[kBuffSize];
    qint64 bytesAvail;
    qint64 bytesRead;

    bytesAvail = _pSocket->bytesAvailable();

    if ( bytesAvail > 0 )
    {
        ::memset(pBuffer, kBuffSize, kBuffSize);
        bytesRead = _pSocket->read(pBuffer, kBuffSize-1);
    }

    delete[] pBuffer;

}
