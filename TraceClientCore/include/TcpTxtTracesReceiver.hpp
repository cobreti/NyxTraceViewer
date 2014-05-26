#ifndef _TCPTXTTRACESRECEIVER_HPP_
#define _TCPTXTTRACESRECEIVER_HPP_

#include <Nyx.hpp>
#include <NyxNet.hpp>
#include <TextTraceHandler.hpp>
#include <NyxWebSvr/ConnHttpHandler.hpp>

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
        
        //
        // IConnectionHandler methods
        //
        
        virtual void HandleStream( Nyx::IStreamRW& rStream );
		virtual Nyx::NyxResult OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::IConnectionHandler*& pCloneHandler );
		virtual void OnConnectionTerminated( NyxNet::IConnection* pConnection );
        virtual void CloseConnection( NyxNet::IConnection* pConnection );
        
        virtual void OnGetRequest_Trace( NyxWebSvr::CConnHttpHandler& rConnHttpHandler, char* szPath, char* szParams );
        virtual void OnPostRequest_Trace( NyxWebSvr::CConnHttpHandler& rConnHttpHandler, char* szPath, char* szParams );
        
    protected:

		virtual void HandleRawTraceLine(char* szLine, const Nyx::NyxSize& size);
		virtual void HandleTraceLine(char* szHeader, char* pThread, char* szContent);
		virtual void SendWebSocketAnswer(char* szInHeader, Nyx::IStreamRW& rStream);
		virtual void SendHttpAnswer(char* szInHeader, Nyx::IStreamRW& rStream);
        virtual void GetClientAddress(NyxNet::IConnection* pConnection);

    protected:
        
        NyxNet::IConnection*            m_pConnection;
        Nyx::TBuffer<Nyx::Byte>         m_Buffer;
        CTcpTxtTracesReceiversSvr*      m_pServer;
        CTracesReceiverProtocol*		m_pProtocol;
        CTextTraceHandler				m_TextTraceHandler;
        NyxWebSvr::CConnHttpHandlerRef  m_refHttpConnHandler;
        NyxNet::CAddress                m_ClientAddress;
    };
}


#endif // _TCPTXTTRACESRECEIVER_HPP_
