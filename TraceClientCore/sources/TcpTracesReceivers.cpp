#include "TcpTracesReceivers.hpp"
#include "TcpTracesReceiver.hpp"


namespace TraceClientCore
{
    /**
     *
     */
    CTcpTracesReceivers::CTcpTracesReceivers()
    {
        
    }
    
    
    /**
     *
     */
    CTcpTracesReceivers::~CTcpTracesReceivers()
    {
        
    }
    
    
    /**
     *
     */
    void CTcpTracesReceivers::Start()
    {
        Nyx::NyxResult      res;
        
        m_refNxConnection = NyxNet::CNxConnection::Alloc();
        m_refNxConnection->SetConnectionHandler( static_cast<NyxNet::INxConnectionHandler*>(this) );
        
        m_refServer = NyxNet::CTcpIpServer::Alloc();
        res = m_refServer->Create(  8500,
                                    100,
                                    m_refNxConnection );
        m_refServer->Start();
        
    }
    
    
    /**
     *
     */
    void CTcpTracesReceivers::Stop()
    {
        if ( m_refServer.Valid() && m_refServer->IsRunning() )
            m_refServer->Stop();
    }
    
    
    /**
     *
     */
    void CTcpTracesReceivers::HandleStream( NyxNet::INxStreamRW& rStream )
    {
    }

    
    /**
     *
     */
    Nyx::NyxResult CTcpTracesReceivers::OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::INxConnectionHandler*& pCloneHandler )
    {
        CTcpTracesReceiver* pReceiver = new CTcpTracesReceiver(pConnection);
        pCloneHandler = static_cast<NyxNet::INxConnectionHandler*>(pReceiver);
        
        return Nyx::kNyxRes_Success;
    }
    
    
    /**
     *
     */
    void CTcpTracesReceivers::OnConnectionTerminated( NyxNet::IConnection* pConnection )
    {
        
    }
}

