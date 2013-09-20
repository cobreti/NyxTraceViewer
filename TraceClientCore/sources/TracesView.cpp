//
//  TracesView.cpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2013-09-19.
//
//

#include "TracesView.hpp"
#include "TracesViewRepoObserver.hpp"
#include "TraceChannel.hpp"
#include "TracesPool.hpp"


namespace TraceClientCore
{
    /**
     *
     */
    CTracesView::CTracesView(CTraceChannel* pChannel) :
    CTracesList(),
    m_pChannel(pChannel),
    m_pRepoObserver(NULL)
    {
        CTraceDataRepository&   rRepository = pChannel->Pool()->Repository();
        m_pRepoObserver = new CTracesViewRepoObserver(this);
        
        rRepository.Insert( m_pRepoObserver );
    }
    
    
    /**
     *
     */
    CTracesView::~CTracesView()
    {
    }
    
    
    /**
     *
     */
    void CTracesView::AddTrace( CTraceData* pTraceData )
    {
        Nyx::TMutexLock     TracesLock(m_refMutex, true);
        
        push_back(pTraceData);
    }
}


