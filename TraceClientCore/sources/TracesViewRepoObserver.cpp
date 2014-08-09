//
//  TracesViewRepoObserver.cpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2013-09-19.
//
//

#include "TracesViewRepoObserver.hpp"
#include "TracesView.hpp"


namespace TraceClientCore
{
    
    /**
     *
     */
    CTracesViewRepoObserver::CTracesViewRepoObserver(CTracesView* pView) : CRepositoryObserver(),
    m_pView(pView)
    {
        
    }
    
    
    /**
     *
     */
    CTracesViewRepoObserver::~CTracesViewRepoObserver()
    {
        
    }
    

    /**
     *
     */
    void CTracesViewRepoObserver::Insert( CTraceData* pTraceData )
    {
        m_pView->AddTrace(pTraceData);
    }
    
    
    /**
     *
     */
    void CTracesViewRepoObserver::BeginClear( const Nyx::CAString& ModuleName )
    {
        
    }
    
    
    /**
     *
     */
    void CTracesViewRepoObserver::EndClear( const Nyx::CAString& ModuleName )
    {
        
    }

    
    /**
     *
     */
    void CTracesViewRepoObserver::OnFirstBeginUpdate()
    {
        m_pView->BeginUpdate();
    }
    
    
    /**
     *
     */
    void CTracesViewRepoObserver::OnFinalEndUpdate()
    {
        m_pView->EndUpdate();
    }
}

