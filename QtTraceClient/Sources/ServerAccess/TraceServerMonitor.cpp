#include <Nyx.hpp>

#include "TraceServerMonitor.h"
#include "TraceServerPortal.h"



CTraceServerMonitor::CTraceServerMonitor(CTraceServerPortal& rServerPortal) : QObject(),
    m_rServerPortal(rServerPortal),
    m_bActive(false)
{
    m_HeartbeatTimer.setInterval(5000);
    m_HeartbeatTimer.setSingleShot(true);

    connect( &m_HeartbeatTimer, SIGNAL(timeout()),
             this, SLOT(onHeartbeatTimeout()) );
    connect( &m_rServerPortal, SIGNAL(heartbeatSuccessfull()),
             this, SLOT(onHeartbeatSuccess()) );
    connect( &m_rServerPortal, SIGNAL(heartbeatFailure()),
             this, SLOT(onHeartbeatFailure()) );
}


CTraceServerMonitor::~CTraceServerMonitor()
{
}



void CTraceServerMonitor::Start()
{
    m_bActive = true;

    checkConnection();
}


void CTraceServerMonitor::Stop()
{
    m_bActive = false;
    m_HeartbeatTimer.stop();
}


void CTraceServerMonitor::onHeartbeatTimeout()
{
    checkConnection();
}


void CTraceServerMonitor::onHeartbeatSuccess()
{
    NYXTRACE(0x0, L"onHeartbeatSuccess");

    if ( active() )
    {
        emit connected();
        m_HeartbeatTimer.start();
    }
}


void CTraceServerMonitor::onHeartbeatFailure()
{
    NYXTRACE(0x0, L"onHeartbeatFailure");

    if ( active() )
    {
        emit connectionLost();
        m_HeartbeatTimer.start();
    }
}


void CTraceServerMonitor::checkConnection()
{
    m_rServerPortal.checkServerConnection();
}
