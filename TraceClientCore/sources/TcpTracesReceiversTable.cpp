//
//  TcpTracesReceiversTable.cpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2012-11-06.
//
//

#include "TcpTracesReceiversTable.hpp"

namespace TraceClientCore
{
    /**
     *
     */
    CTcpTracesReceiversTable::CTcpTracesReceiversTable() :
    m_MethodsImpl(*this)
    {
        m_refMethodsAccessLock = Nyx::CMutex::Alloc();
    }
    
    
    /**
     *
     */
    CTcpTracesReceiversTable::~CTcpTracesReceiversTable()
    {
        
    }
    
    
    
    
    /**
     *
     */
    CTcpTracesReceiversTable::XMethodsImpl::XMethodsImpl( CTcpTracesReceiversTable& rTable ) :
    m_rTable(rTable)
    {
    }
    
    
    /**
     *
     */
    CTcpTracesReceiversTable::XMethodsImpl::~XMethodsImpl()
    {
    }

    
    /**
     *
     */
    void CTcpTracesReceiversTable::XMethodsImpl::Retain() const
    {
        m_rTable.m_refMethodsAccessLock->Lock();
    }
    
    
    /**
     *
     */
    void CTcpTracesReceiversTable::XMethodsImpl::Release() const
    {
        m_rTable.m_refMethodsAccessLock->Unlock();
    }
    
    
    /**
     *
     */
    void CTcpTracesReceiversTable::XMethodsImpl::Insert( CTcpTracesReceiver* pReceiver )
    {
        NYXTRACE(0x0, L"Inserting receiver object " << Nyx::CTF_Ptr(pReceiver) );
    }

    
    /**
     *
     */
    void CTcpTracesReceiversTable::XMethodsImpl::Remove( CTcpTracesReceiver *pReceiver )
    {
        NYXTRACE(0x0, L"Removing receiver object " << Nyx::CTF_Ptr(pReceiver) );        
    }
}
