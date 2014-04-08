#include "PlainFeeder.h"
#include "FeederSettings.hpp"
#include "FeederSource.hpp"

#include <QHostAddress>


CPlainFeeder::CPlainFeeder() : CFeederBase(),
    m_Index(0)
{

}


CPlainFeeder::~CPlainFeeder()
{

}


void CPlainFeeder::OnBegin()
{
    Nyx::CAString       host = Settings().TcpIpAddress();

    QHostAddress        addr(host.c_str());

    m_socket.connectToHost(addr, Settings().PortNumber());

    m_socket.waitForConnected(5000);
}


void CPlainFeeder::OnEnd()
{
    m_socket.disconnect();
}


void CPlainFeeder::OnSendTrace()
{
    if ( Settings().FeederSource() )
    {
        Nyx::CWString   text;
        Nyx::CAString   ansi_text;
        Nyx::CAString   ansi_name;

        Settings().FeederSource()->GetLine(text);

        ansi_name = Settings().Name();
        ansi_text = text;

        QString     dataString = QString("%1/%2").arg(ansi_name.c_str()).arg(ansi_text.c_str());
        QByteArray  data;

        data.append(dataString);
        data.append((char)0);
        m_socket.write(data);
        m_socket.flush();

        m_socket.waitForBytesWritten(5000);
    }
}
