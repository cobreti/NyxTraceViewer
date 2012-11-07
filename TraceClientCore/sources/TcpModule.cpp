#include "TcpModule.hpp"


namespace TraceClientCore
{
    /**
     *
     */
    CTcpModule::CTcpModule()
    {
        m_TracesReceiversSvrTable.push_back(new CTcpTracesReceiversSvr(*this));
        m_TracesReceiversSvrTable.push_back(new CTcpTracesReceiversSvr(*this));
//        m_pTcpTracesReceiversSvr = new CTcpTracesReceiversSvr(*this);
    }
    
    
    /**
     *
     */
    CTcpModule::~CTcpModule()
    {
        for (size_t index = 0; index < m_TracesReceiversSvrTable.size(); ++index)
        {
            delete m_TracesReceiversSvrTable[index];
        }
//        delete m_pTcpTracesReceiversSvr;
    }
}
