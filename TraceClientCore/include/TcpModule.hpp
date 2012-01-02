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
        
        const CTcpTracesReceivers&      TcpTracesReceivers() const      { return m_TcpTracesReceivers; }
        CTcpTracesReceivers&            TcpTracesReceivers()            { return m_TcpTracesReceivers; }
        
    protected:
        
        CTcpTracesReceivers     m_TcpTracesReceivers;
    };
}


#endif // _TCPMODULE_HPP_
