#include "TcpTracesReceiver.hpp"


namespace TraceClientCore
{
    /**
     *
     */
    CTcpTracesReceiver::CTcpTracesReceiver(NyxNet::IConnection* pConnection) :
    m_pConnection(pConnection)
    {
        
    }
    
    
    /**
     *
     */
    CTcpTracesReceiver::~CTcpTracesReceiver()
    {
        
    }
    
    
    /**
     *
     */
    void CTcpTracesReceiver::HandleStream( NyxNet::INxStreamRW& rStream )
    {
    }
    
    
    /**
     *
     */
    Nyx::NyxResult CTcpTracesReceiver::OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::INxConnectionHandler*& pCloneHandler )
    {
        
        return Nyx::kNyxRes_Success;
    }
    
    
    /**
     *
     */
    void CTcpTracesReceiver::OnConnectionTerminated( NyxNet::IConnection* pConnection )
    {
        delete this;
    }
}

