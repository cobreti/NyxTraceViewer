//
//  TracesView.hpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2013-09-19.
//
//

#ifndef TraceClientCore_TracesView_hpp
#define TraceClientCore_TracesView_hpp

#include <Nyx.hpp>

#include "TracesList.hpp"

namespace TraceClientCore
{
    class CTraceChannel;
    class CTraceData;
    class CTracesViewRepoObserver;
    
    
    /**
     *
     */
    class CTracesView : public CTracesList
    {
        friend class CTracesViewRepoObserver;
        
    public:
        CTracesView(CTraceChannel* pChannel);
        virtual ~CTracesView();
        
        CTraceChannel*      Channel() const { return m_pChannel; }
        
    protected:
        
        void AddTrace( CTraceData* pTraceData );
        
    protected:
        
        CTraceChannel*                  m_pChannel;
        CTracesViewRepoObserver*        m_pRepoObserver;
        
    };
}

#endif
