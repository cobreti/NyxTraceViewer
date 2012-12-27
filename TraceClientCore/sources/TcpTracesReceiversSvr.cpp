#include "TcpTracesReceiversSvr.hpp"


namespace TraceClientCore
{
    /**
     *
     */
//    class CServerListenerBridge : public Nyx::CObject_Impl<NyxNet::IServerListener>
//    {
//    public:
//        CServerListenerBridge( CTcpTracesReceiversSvr& rReceivers ) : m_rReceivers(rReceivers) {}
//        virtual ~CServerListenerBridge() {}
//
//        virtual void OnServerStarted( NyxNet::CServer* pServer )
//        {
//            m_rReceivers.Listeners()->OnReceiversStarted();
//        }
//
//        virtual void OnServerStopped( NyxNet::CServer* pServer )
//        {
//            m_rReceivers.Listeners()->OnReceiversStopped();
//        }
//
//    protected:
//
//        CTcpTracesReceiversSvr&        m_rReceivers;
//    };
    
    
    /**
     *
     */
    CTcpTracesReceiversSvr::CTcpTracesReceiversSvr( CTcpModule& rTcpModule ) : m_rTcpModule(rTcpModule)
    {
        m_refListeners = new CTcpTracesReceiversListeners();
        
        NYXTRACE(0x0, L"Receivers created : " << Nyx::CTF_Ptr(this) );
    }
    
    
    /**
     *
     */
    CTcpTracesReceiversSvr::~CTcpTracesReceiversSvr()
    {
        NYXTRACE(0x0, L"Receivers destroyed : " << Nyx::CTF_Ptr(this) );        
    }
    
    
    /**
     *
     */
//    void CTcpTracesReceiversSvr::Start(const CSettings& settings)
//    {
//        Nyx::NyxResult      res;
//
//        m_Settings = settings;
//
//        m_refNxConnection = NyxNet::CNxConnection::Alloc();
//        m_refNxConnection->SetConnectionHandler( static_cast<NyxNet::INxConnectionHandler*>(this) );
//        m_refNxConnection->SetUseHandshake(settings.UseHandshake());
//
//        m_refServer = NyxNet::CTcpIpServer::Alloc();
//        m_refServer->Listeners()->Add( new CServerListenerBridge(*this) );
//        res = m_refServer->Create(  m_Settings.PortNumber(),
//                                    100,
//                                    m_refNxConnection );
//        m_refServer->Start();
//
//    }
    
    
    /**
     *
     */
//    void CTcpTracesReceiversSvr::Stop()
//    {
//        if ( m_refServer.Valid() && m_refServer->IsRunning() )
//            m_refServer->Stop();
//    }
    
    
    /**
     *
     */
//    bool CTcpTracesReceiversSvr::IsRunning()
//    {
//        if ( m_refServer.Valid() )
//            return m_refServer->IsRunning();
//
//        return false;
//    }
    
    
    /**
     *
     */
//    void CTcpTracesReceiversSvr::HandleStream( NyxNet::INxStreamRW& rStream )
//    {
//    }

    
    /**
     *
     */
//    Nyx::NyxResult CTcpTracesReceiversSvr::OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::INxConnectionHandler*& pCloneHandler )
//    {
//        CTcpTracesReceiver* pReceiver = new CTcpTracesReceiver(this, pConnection);
//        pCloneHandler = static_cast<NyxNet::INxConnectionHandler*>(pReceiver);
//
//        return Nyx::kNyxRes_Success;
//    }
    
    
    /**
     *
     */
//    void CTcpTracesReceiversSvr::OnConnectionTerminated( NyxNet::IConnection* pConnection )
//    {
//
//    }
}

