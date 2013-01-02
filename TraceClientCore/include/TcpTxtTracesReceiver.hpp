#ifndef _TCPTXTTRACESRECEIVER_HPP_
#define _TCPTXTTRACESRECEIVER_HPP_

#include <Nyx.hpp>
#include <NyxNet.hpp>

namespace TraceClientCore
{
    class CTcpTxtTracesReceiversSvr;
    class CTraceChannel;
    class CTracesReceiverProtocol;
    
    class CTcpTxtTracesReceiver : public NyxNet::IConnectionHandler
    {
    public:
        CTcpTxtTracesReceiver(CTcpTxtTracesReceiversSvr* pSvr, NyxNet::IConnection* pConnection);
        virtual ~CTcpTxtTracesReceiver();

        CTraceChannel*  LastChannel() const     { return m_pChannel; }
        
        //
        // IConnectionHandler methods
        //
        
        virtual void HandleStream( Nyx::IStreamRW& rStream );
		virtual Nyx::NyxResult OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::IConnectionHandler*& pCloneHandler );
		virtual void OnConnectionTerminated( NyxNet::IConnection* pConnection );
        
    protected:

		virtual void HandleRawTraceLine(char* szLine, const Nyx::NyxSize& size);
		virtual void HandleTraceLine(char* szHeader, char* pThread, char* szContent);
		virtual void SendWebSocketAnswer(char* szInHeader, Nyx::IStreamRW& rStream);

    protected:
        
        NyxNet::IConnection*            m_pConnection;
        Nyx::TBuffer<Nyx::Byte>         m_Buffer;
        CTcpTxtTracesReceiversSvr*      m_pServer;
        CTraceChannel*                  m_pChannel;
        CTracesReceiverProtocol*		m_pProtocol;
    };
}


#endif // _TCPTXTTRACESRECEIVER_HPP_
