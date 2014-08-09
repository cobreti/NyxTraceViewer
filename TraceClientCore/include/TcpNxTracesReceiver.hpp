#ifndef _TCPNXTRACESRECEIVER_HPP_
#define _TCPNXTRACESRECEIVER_HPP_

#include <Nyx.hpp>
#include <NyxNet.hpp>

#include "TraceChannel.hpp"


namespace TraceClientCore
{
    class CTcpNxTracesReceiversSvr;
    class CTraceChannel;
    
    class CTcpNxTracesReceiver : public NyxNet::INxConnectionHandler
    {
    public:
        CTcpNxTracesReceiver(CTcpNxTracesReceiversSvr* pSvr, NyxNet::IConnection* pConnection);
        virtual ~CTcpNxTracesReceiver();

        CTraceChannel*  LastChannel() const     { return m_pChannel; }
        
        //
        // INxConnectionHandler methods
        //
        
		virtual void HandleStream( NyxNet::INxStreamRW& rStream );
		virtual Nyx::NyxResult OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::INxConnectionHandler*& pCloneHandler );
		virtual void OnConnectionTerminated( NyxNet::IConnection* pConnection );
        
    protected:
        
        virtual void HandleTraceStream( NyxNet::CNxStreamReader& rStreamReader );
        virtual void HandleTxtTraceStream( NyxNet::CNxStreamReader& rStreamReader );
        virtual void GetClientAddress(NyxNet::IConnection* pConnection);
        
    protected:
        
        NyxNet::IConnection*            m_pConnection;
        Nyx::TBuffer<Nyx::Byte>         m_Buffer;
        CTcpNxTracesReceiversSvr*       m_pServer;
        CTraceChannel*                  m_pChannel;
        NyxNet::CAddress                m_ClientAddress;
        CTraceChannelSet                m_ChannelsSet;
    };
}


#endif // _TCPNXTRACESRECEIVER_HPP_
