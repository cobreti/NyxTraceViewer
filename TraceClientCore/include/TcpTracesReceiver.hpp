#ifndef _TCPTRACESRECEIVER_HPP_
#define _TCPTRACESRECEIVER_HPP_

#include <Nyx.hpp>
#include <NyxNet.hpp>

namespace TraceClientCore
{
    class CTcpTracesReceivers;
    class CTraceChannel;
    
    class CTcpTracesReceiver : public NyxNet::INxConnectionHandler
    {
    public:
        CTcpTracesReceiver(CTcpTracesReceivers* pSvr, NyxNet::IConnection* pConnection);
        virtual ~CTcpTracesReceiver();

        CTraceChannel*  LastChannel() const     { return m_pChannel; }
        
        //
        // INxConnectionHandler methods
        //
        
		virtual void HandleStream( NyxNet::INxStreamRW& rStream );
		virtual Nyx::NyxResult OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::INxConnectionHandler*& pCloneHandler );
		virtual void OnConnectionTerminated( NyxNet::IConnection* pConnection );
        
    protected:
        
        NyxNet::IConnection*            m_pConnection;
        Nyx::TBuffer<Nyx::Byte>         m_Buffer;
        CTcpTracesReceivers*            m_pServer;
        CTraceChannel*                  m_pChannel;
    };
}


#endif // _TCPTRACESRECEIVER_HPP_
