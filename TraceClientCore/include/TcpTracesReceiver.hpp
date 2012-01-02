#ifndef _TCPTRACESRECEIVER_HPP_
#define _TCPTRACESRECEIVER_HPP_

#include <Nyx.hpp>
#include <NyxNet.hpp>

namespace TraceClientCore
{
    class CTcpTracesReceiver : public NyxNet::INxConnectionHandler
    {
    public:
        CTcpTracesReceiver(NyxNet::IConnection* pConnection);
        virtual ~CTcpTracesReceiver();

        //
        // INxConnectionHandler methods
        //
        
		virtual void HandleStream( NyxNet::INxStreamRW& rStream );
		virtual Nyx::NyxResult OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::INxConnectionHandler*& pCloneHandler );
		virtual void OnConnectionTerminated( NyxNet::IConnection* pConnection );
        
    protected:
        
        NyxNet::IConnection*    m_pConnection;
    };
}


#endif // _TCPTRACESRECEIVER_HPP_
