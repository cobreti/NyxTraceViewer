#ifndef _TCPTRACESRECEIVERS_HPP_
#define _TCPTRACESRECEIVERS_HPP_

#include <Nyx.hpp>
#include <NyxNet.hpp>

namespace TraceClientCore
{
    class CTcpTracesReceivers : public NyxNet::INxConnectionHandler
    {
    public:
        CTcpTracesReceivers();
        virtual ~CTcpTracesReceivers();
        
        virtual void Start();
        virtual void Stop();
        
        //
        // INxConnectionHandler methods
        //
        
		virtual void HandleStream( NyxNet::INxStreamRW& rStream );
		virtual Nyx::NyxResult OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::INxConnectionHandler*& pCloneHandler );
		virtual void OnConnectionTerminated( NyxNet::IConnection* pConnection );
        
    protected:
        
        NyxNet::CNxConnectionRef        m_refNxConnection;
        NyxNet::CTcpIpServerRef         m_refServer;
    };
}


#endif // _TCPTRACESRECEIVERS_HPP_
