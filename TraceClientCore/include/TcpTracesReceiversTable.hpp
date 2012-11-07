//
//  TcpTracesReceiversTable.hpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2012-11-06.
//
//

#ifndef _TCPTRACESRECEIVERSTABLE_HPP_
#define _TCPTRACESRECEIVERSTABLE_HPP_

#include <Nyx.hpp>

namespace TraceClientCore
{
    class CTcpTracesReceiver;
    
    /**
     *
     */
    class CTcpTracesReceiversTable
    {        
    public:
        
        /**
         *
         */
        class XMethods
        {
        public:
            XMethods() {}
            virtual ~XMethods() {}
            
            virtual void Retain() const = 0;
            virtual void Release() const = 0;
            
            virtual void Insert( CTcpTracesReceiver* pReceiver ) = 0;
            virtual void Remove( CTcpTracesReceiver* pReceiver ) = 0;
        };
        
        typedef     Nyx::CRef<XMethods>     MethodsRef;
        
    public:
        CTcpTracesReceiversTable();
        virtual ~CTcpTracesReceiversTable();

        MethodsRef GetMethods()     { return &m_MethodsImpl; }

    protected:
        
        /**
         *
         */
        class XMethodsImpl : public XMethods
        {
        public:
            XMethodsImpl( CTcpTracesReceiversTable& rTable );
            virtual ~XMethodsImpl();
            
            void Retain() const;
            void Release() const;
            
            virtual void Insert( CTcpTracesReceiver* pReceiver );
            virtual void Remove( CTcpTracesReceiver* pReceiver );

        protected:
            
            CTcpTracesReceiversTable&   m_rTable;
        };
        
    protected:
        
        Nyx::CMutexRef      m_refMethodsAccessLock;
        XMethodsImpl        m_MethodsImpl;
    };
}


#endif
