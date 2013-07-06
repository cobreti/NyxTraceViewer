#ifndef _TCPTXTTRACESRECEIVERS_HPP_
#define _TCPTXTTRACESRECEIVERS_HPP_

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
    class CTcpTxtTracesReceiversSvr : 	public CTcpTracesReceiversSvr,
    									public NyxNet::IConnectionHandler
    {
    public:
        CTcpTxtTracesReceiversSvr( CTcpModule& rTcpModule );
        virtual ~CTcpTxtTracesReceiversSvr();

        virtual void Start(const CSettings& settings);
        virtual void Stop();
        virtual bool IsRunning();
        virtual bool GetUseSSL() const;

        //
        // INxConnectionHandler methods
        //
        
        virtual void HandleStream( Nyx::IStreamRW& rStream );
		virtual Nyx::NyxResult OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::IConnectionHandler*& pCloneHandler );
		virtual void OnConnectionTerminated( NyxNet::IConnection* pConnection );
        virtual void CloseConnection( NyxNet::IConnection* pConnection );
        
    protected:
        
        NyxNet::CTcpIpServerRef             m_refServer;
    };
}


#endif // _TCPTXTTRACESRECEIVERS_HPP_
