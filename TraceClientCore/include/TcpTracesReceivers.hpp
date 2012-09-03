#ifndef _TCPTRACESRECEIVERS_HPP_
#define _TCPTRACESRECEIVERS_HPP_

#include <Nyx.hpp>
#include <NyxNet.hpp>

#include "TcpTracesReceiversListener.hpp"

namespace TraceClientCore
{
    /**
     *
     */
    class CTcpTracesReceivers : public NyxNet::INxConnectionHandler
    {
    public:
        
        /**
         *
         */
        class CSettings
        {
        public:
            CSettings() : m_PortNumber(0) {}
            CSettings(const CSettings& settings ) : m_PortNumber(settings.m_PortNumber) {}
            ~CSettings() {}
            
            const CSettings& operator = (const CSettings& settings)
            {
                m_PortNumber = settings.m_PortNumber;
                return *this;
            }
            
            const Nyx::UInt32&  PortNumber() const      { return m_PortNumber; }
            Nyx::UInt32&        PortNumber()            { return m_PortNumber; }
            
        protected:
            Nyx::UInt32     m_PortNumber;
        };
        
    public:
        CTcpTracesReceivers();
        virtual ~CTcpTracesReceivers();
        
        CTcpTracesReceiversListenersRef     Listeners()     { return m_refListeners; }
        
        virtual void Start(const CSettings& settings);
        virtual void Stop();
        virtual bool IsRunning();
        
        const CSettings&        Settings() const    { return m_Settings; }
        
        //
        // INxConnectionHandler methods
        //
        
		virtual void HandleStream( NyxNet::INxStreamRW& rStream );
		virtual Nyx::NyxResult OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::INxConnectionHandler*& pCloneHandler );
		virtual void OnConnectionTerminated( NyxNet::IConnection* pConnection );
        
    protected:
        
        NyxNet::CNxConnectionRef            m_refNxConnection;
        NyxNet::CTcpIpServerRef             m_refServer;
        CTcpTracesReceiversListenersRef     m_refListeners;
        CSettings                           m_Settings;
    };
}


#endif // _TCPTRACESRECEIVERS_HPP_
