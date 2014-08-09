#ifndef PLAINFEEDER_H
#define PLAINFEEDER_H

#include <Nyx.hpp>
#include "FeederBase.hpp"

#include <QTcpSocket>

class CPlainFeeder : public CFeederBase
{
public:
    CPlainFeeder();
    virtual ~CPlainFeeder();

protected:

    virtual void OnBegin();
    virtual void OnEnd();
    virtual void OnSendTrace();

protected:

    Nyx::CTraceCompositorRef        m_refTraceCompositor;
    int                             m_Index;
    QTcpSocket                      m_socket;
};

#endif // PLAINFEEDER_H
