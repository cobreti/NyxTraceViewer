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
    class CTcpTracesReceiversSvr : public NyxNet::INxConnectionHandler
    {
    public:
        
        /**
         *
         */
        class CSettings
        {
        public:
            CSettings() : m_PortNumber(0), m_bUseHandshake(true) {}
            CSettings(const CSettings& settings ) :
                m_PortNumber(settings.m_PortNumber),
                m_bUseHandshake(settings.m_bUseHandshake) {}
            ~CSettings() {}
            
            const CSettings& operator = (const CSettings& settings)
            {
                m_PortNumber = settings.m_PortNumber;
                m_bUseHandshake = settings.m_bUseHandshake;
                return *this;
            }
            
            const Nyx::UInt32&  PortNumber() const      { return m_PortNumber; }
            Nyx::UInt32&        PortNumber()            { return m_PortNumber; }
            
            const bool          UseHandshake() const    { return m_bUseHandshake; }
            bool&               UseHandshake()          { return m_bUseHandshake; }
            
        protected:
            Nyx::UInt32     m_PortNumber;
            bool            m_bUseHandshake;
        };
        
    public:
        CTcpTracesReceiversSvr( CTcpModule& rTcpModule );
        virtual ~CTcpTracesReceiversSvr();
        
        CTcpTracesReceiversListenersRef     Listeners()     { return m_refListeners; }
        
        virtual void Start(const CSettings& settings);
        virtual void Stop();
        virtual bool IsRunning();
        
        const CSettings&        Settings() const    { return m_Settings; }
        
        CTcpTracesReceiversTable& ReceiversTable()  { return m_ReceiversTable; }
        
        //
        // INxConnectionHandler methods
        //
        
		virtual void HandleStream( NyxNet::INxStreamRW& rStream );
		virtual Nyx::NyxResult OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::INxConnectionHandler*& pCloneHandler );
		virtual void OnConnectionTerminated( NyxNet::IConnection* pConnection );
        
    protected:
        
        CTcpModule&                         m_rTcpModule;
        NyxNet::CNxConnectionRef            m_refNxConnection;
        NyxNet::CTcpIpServerRef             m_refServer;
        CTcpTracesReceiversListenersRef     m_refListeners;
        CSettings                           m_Settings;
        CTcpTracesReceiversTable            m_ReceiversTable;
    };
}


#endif // _TCPTRACESRECEIVERS_HPP_
