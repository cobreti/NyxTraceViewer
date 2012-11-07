#ifndef _TCPMODULE_HPP_
#define _TCPMODULE_HPP_

#include <Nyx.hpp>

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
        
        const CTcpTracesReceiversSvr&      TcpTracesReceiversSvr() const      { return *m_pTcpTracesReceiversSvr; }
        CTcpTracesReceiversSvr&            TcpTracesReceiversSvr()            { return *m_pTcpTracesReceiversSvr; }
        
    protected:
        
        CTcpTracesReceiversSvr*    m_pTcpTracesReceiversSvr;
    };
}


#endif // _TCPMODULE_HPP_
