#include "TcpTxtTracesReceiversSvr.hpp"
#include "TcpTxtTracesReceiver.hpp"

namespace TraceClientCore
{
    /**
     *
     */
    class CTxtServerListenerBridge : public Nyx::CObject_Impl<NyxNet::IServerListener>
    {
    public:
        CTxtServerListenerBridge( CTcpTxtTracesReceiversSvr& rReceivers ) : m_rReceivers(rReceivers) {}
        virtual ~CTxtServerListenerBridge() {}

        virtual void OnServerStarted( NyxNet::CServer* pServer )
        {
            m_rReceivers.Listeners()->OnReceiversStarted();
        }
        
        virtual void OnServerStopped( NyxNet::CServer* pServer )
        {
            m_rReceivers.Listeners()->OnReceiversStopped();
        }
        
    protected:
        
        CTcpTxtTracesReceiversSvr&        m_rReceivers;
    };
    
    
    /**
     *
     */
    CTcpTxtTracesReceiversSvr::CTcpTxtTracesReceiversSvr( CTcpModule& rTcpModule ) :
    		CTcpTracesReceiversSvr(rTcpModule)
    {
    }
    
    
    /**
     *
     */
    CTcpTxtTracesReceiversSvr::~CTcpTxtTracesReceiversSvr()
    {
    }
    
    
    /**
     *
     */
    void CTcpTxtTracesReceiversSvr::Start(const CSettings& settings)
    {
        Nyx::NyxResult      res;
        
        m_Settings = settings;
        
//        m_refNxConnection = NyxNet::CNxConnection::Alloc();
//        m_refNxConnection->SetConnectionHandler( static_cast<NyxNet::INxConnectionHandler*>(this) );
//        m_refNxConnection->SetUseHandshake(settings.UseHandshake());
        
        m_refServer = NyxNet::CTcpIpServer::Alloc();
        
        if ( settings.UseSSL() )
        {
            m_refServer->SetUseSSL();
            NYXTRACE(0x0, L"PrivKey File : " << Nyx::CTF_AnsiText(settings.PrivKeyFile().c_str()) );
            NYXTRACE(0x0, L"Certificate File : " << Nyx::CTF_AnsiText(settings.CertificateFile().c_str()) );
            NYXTRACE(0x0, L"Dh File : " << Nyx::CTF_AnsiText(settings.DhFile().c_str()) );
            m_refServer->SetSSLFiles(settings.PrivKeyFile(), settings.CertificateFile(), settings.DhFile());
        }
        
        m_refServer->Listeners()->Add( new CTxtServerListenerBridge(*this) );
        res = m_refServer->Create(  m_Settings.PortNumber(),
                                    100,
                                    static_cast<NyxNet::IConnectionHandler*>(this) );
        m_refServer->Start();
        
    }
    
    
    /**
     *
     */
    void CTcpTxtTracesReceiversSvr::Stop()
    {
        if ( m_refServer.Valid() && m_refServer->IsRunning() )
            m_refServer->Stop();
    }
    
    
    /**
     *
     */
    bool CTcpTxtTracesReceiversSvr::IsRunning()
    {
        if ( m_refServer.Valid() )
            return m_refServer->IsRunning();
        
        return false;
    }

    
    /**
     *
     */
    bool CTcpTxtTracesReceiversSvr::GetUseSSL() const
    {
        return m_refServer->GetUseSSL();
    }
    
    
    /**
     *
     */
    void CTcpTxtTracesReceiversSvr::HandleStream( Nyx::IStreamRW& rStream )
    {

    }


    /**
     *
     */
    Nyx::NyxResult CTcpTxtTracesReceiversSvr::OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::IConnectionHandler*& pCloneHandler )
    {
        NyxNet::CSocketRef refSocket = pConnection->Socket();
        NyxNet::CAddress clientAddress = refSocket->TcpIpSocket()->ClientAddress();

        CTcpTxtTracesReceiver* pReceiver = new CTcpTxtTracesReceiver(this, pConnection);
        pCloneHandler = static_cast<NyxNet::IConnectionHandler*>(pReceiver);
        
        return Nyx::kNyxRes_Success;
    }
    
    
    /**
     *
     */
    void CTcpTxtTracesReceiversSvr::OnConnectionTerminated( NyxNet::IConnection* pConnection )
    {
        
    }
    
    
    /**
     *
     */
    void CTcpTxtTracesReceiversSvr::CloseConnection( NyxNet::IConnection* pConnection )
    {
        
    }
}

