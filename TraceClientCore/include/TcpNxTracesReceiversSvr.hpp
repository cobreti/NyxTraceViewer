#ifndef _TCPNXTRACESRECEIVERS_HPP_
#define _TCPNXTRACESRECEIVERS_HPP_

#include <Nyx.hpp>
#include <NyxNet.hpp>

#include "TcpTracesReceiversListener.hpp"
#include "TcpTracesReceiversTable.hpp"
#include "TcpTracesReceiversSvr.hpp"

namespace TraceClientCore
{
    class CTcpModule;

    /**
     *
     */
    class CTcpNxTracesReceiversSvr : 	public CTcpTracesReceiversSvr,
    									public NyxNet::INxConnectionHandler
    {
    public:
        CTcpNxTracesReceiversSvr( CTcpModule& rTcpModule );
        virtual ~CTcpNxTracesReceiversSvr();

        virtual void Start(const CSettings& settings);
        virtual void Stop();
        virtual bool IsRunning();

        //
        // INxConnectionHandler methods
        //
        
		virtual void HandleStream( NyxNet::INxStreamRW& rStream );
		virtual Nyx::NyxResult OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::INxConnectionHandler*& pCloneHandler );
		virtual void OnConnectionTerminated( NyxNet::IConnection* pConnection );
        
    protected:
        
        NyxNet::CNxConnectionRef            m_refNxConnection;
        NyxNet::CTcpIpServerRef             m_refServer;
    };
}


#endif // _TCPNXTRACESRECEIVERS_HPP_
