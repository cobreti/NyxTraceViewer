//
//  TracesGroup.cpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2013-09-18.
//
//

#include "TracesGroup.hpp"
#include "TracesView.hpp"
#include "TraceChannel.hpp"
#include "TracesPool.hpp"
#include "MultiViewTracesIterator.hpp"

#include <algorithm>

namespace TraceClientCore
{
    TracesGroupId   CTracesGroup::s_NextAvailId = 1;
    
    
    /**
     *
     */
    CTracesGroup::CTracesGroup() :
    m_Id( CTracesGroup::s_NextAvailId ++ )
    {
        
    }
    
    
    /**
     *
     */
    CTracesGroup::~CTracesGroup()
    {
        
    }
    
    
    /**
     *
     */
    void CTracesGroup::AddChannel( CTraceChannel* pChannel )
    {
        CTracesView*            pView = new CTracesView(pChannel);
        
        pView->Listeners().Add( static_cast<ITracesViewNotificationsListener*>(this) );

        m_Views.push_back(pView);
    }
    
    
    /**
     *
     */
    bool CTracesGroup::HasChannel( CTraceChannel* pChannel )
    {
        TTracesViews::const_iterator        pos = m_Views.begin();
        
        while (pos != m_Views.end())
        {
            if ( pChannel == (*pos)->Channel() )
                return true;
            
            ++ pos;
        }
        
        return false;
    }
    
    
    /**
     *
     */
    CMultiViewTracesIterator CTracesGroup::FirstPos()
    {
        CMultiViewTracesIterator            pos;
        TTracesViews::const_iterator        viewPos = m_Views.begin();
        
        pos.m_pTracesGroup = this;
        
        while (viewPos != m_Views.end())
        {
            CTracesIterator     tracePos = (*viewPos)->FirstPos();
            pos.m_Iterators[*viewPos] = tracePos;
            
            if ( tracePos.Valid() && pos.m_pCurrentView == NULL )
            {
                pos.m_pCurrentView = *viewPos;
                pos.m_CurrentPos = tracePos;
            }
            
            ++ viewPos;
        }
        
        return pos;
    }
    
    
    /**
     *
     */
    CMultiViewTracesIterator CTracesGroup::LastPos()
    {
        CMultiViewTracesIterator            pos;
        TTracesViews::const_iterator        viewPos = m_Views.begin();
        
        pos.m_pTracesGroup = this;
        
        while (viewPos != m_Views.end())
        {
            CTracesIterator     tracePos = (*viewPos)->LastPos();
            pos.m_Iterators[*viewPos] = tracePos;
            
            if ( tracePos.Valid() && pos.m_pCurrentView == NULL )
            {
                pos.m_pCurrentView = *viewPos;
                pos.m_CurrentPos = tracePos;
            }
            
            ++ viewPos;
        }
        
        return pos;
    }
    
    
    /**
     *
     */
    Nyx::UInt32 CTracesGroup::LinesCount() const
    {
        Nyx::UInt32                         count = 0;
        TTracesViews::const_iterator        viewPos = m_Views.begin();
        
        while (viewPos != m_Views.end())
        {
            count += (*viewPos)->LinesCount();
            ++ viewPos;
        }
        
        return count;
    }
    

    void CTracesGroup::Clear()
    {
        auto fctPtr = [] ( CTracesView* pView ) { pView->Clear(); };

        std::for_each( m_Views.begin(), m_Views.end(), fctPtr );
    }

    
    /**
     *
     */
    void CTracesGroup::OnViewBeginUpdate(TraceClientCore::CTracesView *pView)
    {
        m_Listeners.OnViewBeginUpdate(this, pView);
    }
    
    
    /**
     *
     */
    void CTracesGroup::OnViewEndUpdate(TraceClientCore::CTracesView *pView)
    {
        m_Listeners.OnViewEndUpdate(this, pView);
    }
    
    
    /**********************************************************
            CTracesGroupNotificationsListeners
     *********************************************************/
    
    /**
     *
     */
    CTracesGroupNotificationsListeners::CTracesGroupNotificationsListeners()
    {
        
    }
    
    
    /**
     *
     */
    CTracesGroupNotificationsListeners::~CTracesGroupNotificationsListeners()
    {
        
    }
    
    
    /**
     *
     */
    void CTracesGroupNotificationsListeners::Add( ITracesGroupNotificationsListener* pListener )
    {
        m_Listeners.push_back(pListener);
    }
    
    
    /**
     *
     */
    void CTracesGroupNotificationsListeners::Remove(TraceClientCore::ITracesGroupNotificationsListener *pListener)
    {
        TTracesGroupListeners::iterator         pos = m_Listeners.begin();
        
        while (pos != m_Listeners.end())
        {
            if ( *pos == pListener )
            {
                m_Listeners.erase(pos);
                break;
            }
            
            ++ pos;
        }
    }
    
    
    /**
     *
     */
    void CTracesGroupNotificationsListeners::OnViewBeginUpdate(TraceClientCore::CTracesGroup *pGroup, TraceClientCore::CTracesView *pView)
    {
        TTracesGroupListeners::const_iterator           pos = m_Listeners.begin();
        
        while (pos != m_Listeners.end())
        {
            (*pos)->OnViewBeginUpdate(pGroup, pView);
            ++ pos;
        }
    }
    
    
    /**
     *
     */
    void CTracesGroupNotificationsListeners::OnViewEndUpdate(TraceClientCore::CTracesGroup *pGroup, TraceClientCore::CTracesView *pView)
    {
        TTracesGroupListeners::const_iterator           pos = m_Listeners.begin();
        
        while (pos != m_Listeners.end())
        {
            (*pos)->OnViewEndUpdate(pGroup, pView);
            ++ pos;
        }
    }
}



