//
//  TracesViewRepoObserver.hpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2013-09-19.
//
//

#ifndef TraceClientCore_TracesViewRepoObserver_hpp
#define TraceClientCore_TracesViewRepoObserver_hpp

#include "RepositoryObserver.hpp"

namespace TraceClientCore
{
    class CTracesView;
    
    class CTracesViewRepoObserver : public CRepositoryObserver
    {
    public:
        CTracesViewRepoObserver( CTracesView* pView );
        virtual ~CTracesViewRepoObserver();
        
        virtual void Insert( CTraceData* pTraceData );
        virtual void BeginClear( const Nyx::CAString& ModuleName );
        virtual void EndClear( const Nyx::CAString& ModuleName );

    protected:
        
        virtual void OnFirstBeginUpdate();
        virtual void OnFinalEndUpdate();
        
    protected:
        
        CTracesView*        m_pView;
    };
}


#endif
