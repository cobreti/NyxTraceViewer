#ifndef _TCPTRACESRECEIVERS_HPP_
#define _TCPTRACESRECEIVERS_HPP_

#include <Nyx.hpp>
#include <NyxNet.hpp>

#include "TcpTracesReceiversListener.hpp"
#include "TcpTracesReceiversTable.hpp"

namespace TraceClientCore
{
    class CTcpModule;

    /**
     *
     */
    class CTcpTracesReceiversSvr // : public NyxNet::INxConnectionHandler
    {
    public:
        
        /**
         *
         */
        class CSettings
        {
        public:
            CSettings() : m_PortNumber(0), m_bUseHandshake(true), m_bUseSSL(false) {}
            CSettings(const CSettings& settings ) :
                m_PortNumber(settings.m_PortNumber),
                m_bUseHandshake(settings.m_bUseHandshake),
                m_bUseSSL(settings.m_bUseSSL),
                m_certificateFile(settings.m_certificateFile),
                m_privKeyFile(settings.m_privKeyFile),
                m_dhFile(settings.m_dhFile)
            {}
            ~CSettings() {}
            
            const CSettings& operator = (const CSettings& settings)
            {
                m_PortNumber = settings.m_PortNumber;
                m_bUseHandshake = settings.m_bUseHandshake;
                m_bUseSSL = settings.m_bUseSSL;
                m_certificateFile = settings.m_certificateFile;
                m_privKeyFile = settings.m_privKeyFile;
                m_dhFile = settings.m_dhFile;
                return *this;
            }
            
            const Nyx::UInt32&  PortNumber() const      { return m_PortNumber; }
            Nyx::UInt32&        PortNumber()            { return m_PortNumber; }
            
            const bool          UseHandshake() const    { return m_bUseHandshake; }
            bool&               UseHandshake()          { return m_bUseHandshake; }
            
            const bool          UseSSL() const          { return m_bUseSSL; }
            bool&               UseSSL()                { return m_bUseSSL; }
            
            const Nyx::CAString&    CertificateFile() const         { return m_certificateFile; }
            Nyx::CAString&          CertificateFile()               { return m_certificateFile; }
            
            const Nyx::CAString&    PrivKeyFile() const             { return m_privKeyFile; }
            Nyx::CAString&          PrivKeyFile()                   { return m_privKeyFile; }
            
            const Nyx::CAString&    DhFile() const                  { return m_dhFile; }
            Nyx::CAString&          DhFile()                        { return m_dhFile; }

        protected:
            Nyx::UInt32     m_PortNumber;
            bool            m_bUseHandshake;
            bool            m_bUseSSL;
            Nyx::CAString   m_certificateFile;
            Nyx::CAString   m_privKeyFile;
            Nyx::CAString   m_dhFile;
        };
        
    public:
        CTcpTracesReceiversSvr( CTcpModule& rTcpModule );
        virtual ~CTcpTracesReceiversSvr();
        
        CTcpTracesReceiversListenersRef     Listeners()     { return m_refListeners; }
        
        virtual void Start(const CSettings& settings) = 0;
        virtual void Stop() = 0;
        virtual bool IsRunning() = 0;
        
        const CSettings&        Settings() const    { return m_Settings; }
        
//        CTcpTracesReceiversTable& ReceiversTable()  { return m_ReceiversTable; }
        
//        //
//        // INxConnectionHandler methods
//        //
//
//		virtual void HandleStream( NyxNet::INxStreamRW& rStream );
//		virtual Nyx::NyxResult OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::INxConnectionHandler*& pCloneHandler );
//		virtual void OnConnectionTerminated( NyxNet::IConnection* pConnection );
        
    protected:
        
        CTcpModule&                         m_rTcpModule;
//        NyxNet::CNxConnectionRef            m_refNxConnection;
//        NyxNet::CTcpIpServerRef             m_refServer;
        CTcpTracesReceiversListenersRef     m_refListeners;
        CSettings                           m_Settings;
//        CTcpTracesReceiversTable            m_ReceiversTable;
    };
}


#endif // _TCPTRACESRECEIVERS_HPP_
