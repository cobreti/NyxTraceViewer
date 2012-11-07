#ifndef _TCPMODULE_HPP_
#define _TCPMODULE_HPP_

#include <Nyx.hpp>

#include "TcpTracesReceivers.hpp"

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
        
        const CTcpTracesReceivers&      TcpTracesReceivers() const      { return *m_pTcpTracesReceivers; }
        CTcpTracesReceivers&            TcpTracesReceivers()            { return *m_pTcpTracesReceivers; }
        
    protected:
        
        CTcpTracesReceivers*    m_pTcpTracesReceivers;
    };
}


#endif // _TCPMODULE_HPP_
