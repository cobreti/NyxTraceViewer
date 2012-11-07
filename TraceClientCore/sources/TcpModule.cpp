#include "TcpModule.hpp"


namespace TraceClientCore
{
    /**
     *
     */
    CTcpModule::CTcpModule() : m_pTcpTracesReceiversSvr(NULL)
    {
        m_pTcpTracesReceiversSvr = new CTcpTracesReceiversSvr(*this);
    }
    
    
    /**
     *
     */
    CTcpModule::~CTcpModule()
    {
        delete m_pTcpTracesReceiversSvr;
    }
}
