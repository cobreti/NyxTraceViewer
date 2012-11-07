#include "TcpModule.hpp"


namespace TraceClientCore
{
    /**
     *
     */
    CTcpModule::CTcpModule() : m_pTcpTracesReceivers(NULL)
    {
        m_pTcpTracesReceivers = new CTcpTracesReceivers(*this);
    }
    
    
    /**
     *
     */
    CTcpModule::~CTcpModule()
    {
        delete m_pTcpTracesReceivers;
    }
}
