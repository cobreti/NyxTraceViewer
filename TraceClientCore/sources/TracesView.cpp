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
    TracesViewId        CTracesView::s_NextId = 1;
    
    
    
    /**
     *
     */
    CTracesView::CTracesView(CTraceChannel* pChannel) :
    CTracesList(),
    m_pChannel(pChannel),
    m_pRepoObserver(NULL),
    m_Id(s_NextId++),
    m_bDirty(false)
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
     * @brief CTracesView::ResetDirty
     */
    void CTracesView::ResetDirty()
    {
        m_bDirty = false;
    }

    
    /**
     *
     */
    Nyx::UInt32 CTracesView::LinesCount() const
    {
        return size();
    }


    void CTracesView::Clear()
    {
        CTracesList::clear();
    }
    
    
    /**
     *
     */
    void CTracesView::AddTrace( CTraceData* pTraceData )
    {
        Nyx::TMutexLock     TracesLock(m_refMutex, true);
        
        m_bDirty = true;
        push_back(pTraceData);
    }
    
    
    /**
     *
     */
    void CTracesView::BeginUpdate()
    {
        m_Listeners.OnViewBeginUpdate(this);
    }
    
    
    /**
     *
     */
    void CTracesView::EndUpdate()
    {
        m_Listeners.OnViewEndUpdate(this);
    }
    
    
    /**********************************************************
            CTracesViewNotificationsListeners
     *********************************************************/
    
    
    /**
     *
     */
    CTracesViewNotificationsListeners::CTracesViewNotificationsListeners()
    {
        
    }
    
    
    /**
     *
     */
    CTracesViewNotificationsListeners::~CTracesViewNotificationsListeners()
    {
        
    }
    
    
    /**
     *
     */
    void CTracesViewNotificationsListeners::Add(TraceClientCore::ITracesViewNotificationsListener *pListener)
    {
        m_Listeners.push_back(pListener);
    }
    
    
    /**
     *
     */
    void CTracesViewNotificationsListeners::OnViewBeginUpdate(TraceClientCore::CTracesView *pView)
    {
        TListeners::const_iterator          pos = m_Listeners.begin();
        
        while ( pos != m_Listeners.end())
        {
            (*pos)->OnViewBeginUpdate(pView);
            ++ pos;
        }
    }
    
    
    /**
     *
     */
    void CTracesViewNotificationsListeners::OnViewEndUpdate(TraceClientCore::CTracesView *pView)
    {
        TListeners::const_iterator          pos = m_Listeners.begin();
        
        while ( pos != m_Listeners.end())
        {
            (*pos)->OnViewEndUpdate(pView);
            ++ pos;
        }
    }
}


