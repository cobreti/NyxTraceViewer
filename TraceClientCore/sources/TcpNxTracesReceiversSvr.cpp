#include "TcpNxTracesReceiversSvr.hpp"
#include "TcpNxTracesReceiver.hpp"


namespace TraceClientCore
{
    /**
     *
     */
    class CNxServerListenerBridge : public Nyx::CObject_Impl<NyxNet::IServerListener>
    {
    public:
        CNxServerListenerBridge( CTcpNxTracesReceiversSvr& rReceivers ) : m_rReceivers(rReceivers) {}
        virtual ~CNxServerListenerBridge() {}

        virtual void OnServerStarted( NyxNet::CServer* pServer )
        {
            m_rReceivers.Listeners()->OnReceiversStarted();
        }
        
        virtual void OnServerStopped( NyxNet::CServer* pServer )
        {
            m_rReceivers.Listeners()->OnReceiversStopped();
        }
        
    protected:
        
        CTcpNxTracesReceiversSvr&        m_rReceivers;
    };
    
    
    /**
     *
     */
    CTcpNxTracesReceiversSvr::CTcpNxTracesReceiversSvr( CTcpModule& rTcpModule ) :
    		CTcpTracesReceiversSvr(rTcpModule)
    {
    }
    
    
    /**
     *
     */
    CTcpNxTracesReceiversSvr::~CTcpNxTracesReceiversSvr()
    {
    }
    
    
    /**
     *
     */
    void CTcpNxTracesReceiversSvr::Start(const CSettings& settings)
    {
        Nyx::NyxResult      res;
        
        m_Settings = settings;
        
        m_refNxConnection = NyxNet::CNxConnection::Alloc();
        m_refNxConnection->SetConnectionHandler( static_cast<NyxNet::INxConnectionHandler*>(this) );
        m_refNxConnection->SetUseHandshake(settings.UseHandshake());
        
        m_refServer = NyxNet::CTcpIpServer::Alloc();
        m_refServer->Listeners()->Add( new CNxServerListenerBridge(*this) );
        res = m_refServer->Create(  m_Settings.PortNumber(),
                                    100,
                                    m_refNxConnection );
        m_refServer->Start();
        
    }
    
    
    /**
     *
     */
    void CTcpNxTracesReceiversSvr::Stop()
    {
        if ( m_refServer.Valid() && m_refServer->IsRunning() )
            m_refServer->Stop();
    }
    
    
    /**
     *
     */
    bool CTcpNxTracesReceiversSvr::IsRunning()
    {
        if ( m_refServer.Valid() )
            return m_refServer->IsRunning();
        
        return false;
    }
    
    
    /**
     *
     */
    void CTcpNxTracesReceiversSvr::HandleStream( NyxNet::INxStreamRW& rStream )
    {
    }

    
    /**
     *
     */
    Nyx::NyxResult CTcpNxTracesReceiversSvr::OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::INxConnectionHandler*& pCloneHandler )
    {
        CTcpNxTracesReceiver* pReceiver = new CTcpNxTracesReceiver(this, pConnection);
        pCloneHandler = static_cast<NyxNet::INxConnectionHandler*>(pReceiver);
        
        return Nyx::kNyxRes_Success;
    }
    
    
    /**
     *
     */
    void CTcpNxTracesReceiversSvr::OnConnectionTerminated( NyxNet::IConnection* pConnection )
    {
        
    }
}

