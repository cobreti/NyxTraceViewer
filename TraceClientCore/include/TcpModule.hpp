#ifndef _TCPMODULE_HPP_
#define _TCPMODULE_HPP_

#include <Nyx.hpp>
#include <vector>

#include "TcpTracesReceiversSvr.hpp"

namespace TraceClientCore
{
    /**
     *
     */
    class CTcpModule
    {
    public:
        CTcpModule();
        virtual ~CTcpModule();
        
        const CTcpTracesReceiversSvr&      TcpTracesReceiversSvr(size_t index) const      { return *m_TracesReceiversSvrTable[index]; }
        CTcpTracesReceiversSvr&            TcpTracesReceiversSvr(size_t index)            { return *m_TracesReceiversSvrTable[index]; }
        
    protected:
        
        typedef std::vector<CTcpTracesReceiversSvr*> TracesReceiversSvrTableType;
        
    protected:
        
        TracesReceiversSvrTableType         m_TracesReceiversSvrTable;
//        CTcpTracesReceiversSvr*     m_pTcpTracesReceiversSvr;
//        CTcpTracesReceiversSvr*     m_pTcpTracesReceiversSvr2;
    };
}


#endif // _TCPMODULE_HPP_
