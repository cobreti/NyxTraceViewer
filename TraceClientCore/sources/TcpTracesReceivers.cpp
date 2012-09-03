#include "TcpTracesReceivers.hpp"
#include "TcpTracesReceiver.hpp"


namespace TraceClientCore
{
    /**
     *
     */
    class CServerListenerBridge : public Nyx::CObject_Impl<NyxNet::IServerListener>
    {
    public:
        CServerListenerBridge( CTcpTracesReceivers& rReceivers ) : m_rReceivers(rReceivers) {}
        virtual ~CServerListenerBridge() {}

        virtual void OnServerStarted( NyxNet::CServer* pServer )
        {
            m_rReceivers.Listeners()->OnReceiversStarted();
        }
        
        virtual void OnServerStopped( NyxNet::CServer* pServer )
        {
            m_rReceivers.Listeners()->OnReceiversStopped();
        }
        
    protected:
        
        CTcpTracesReceivers&        m_rReceivers;
    };
    
    
    /**
     *
     */
    CTcpTracesReceivers::CTcpTracesReceivers()
    {
        m_refListeners = new CTcpTracesReceiversListeners();
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
    void CTcpTracesReceivers::Start(const CSettings& settings)
    {
        Nyx::NyxResult      res;
        
        m_Settings = settings;
        
        m_refNxConnection = NyxNet::CNxConnection::Alloc();
        m_refNxConnection->SetConnectionHandler( static_cast<NyxNet::INxConnectionHandler*>(this) );
        
        m_refServer = NyxNet::CTcpIpServer::Alloc();
        m_refServer->Listeners()->Add( new CServerListenerBridge(*this) );
        res = m_refServer->Create(  m_Settings.PortNumber(),
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
    bool CTcpTracesReceivers::IsRunning()
    {
        if ( m_refServer.Valid() )
            return m_refServer->IsRunning();
        
        return false;
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

