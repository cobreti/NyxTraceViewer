//
//  TracesView.hpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2013-09-19.
//
//

#ifndef TraceClientCore_TracesView_hpp
#define TraceClientCore_TracesView_hpp

namespace TraceClientCore
{
    class CTraceChannel;
    
    
    /**
     *
     */
    class CTracesView
    {
    public:
        CTracesView(CTraceChannel* pChannel);
        virtual ~CTracesView();
        
        CTraceChannel*      Channel() const { return m_pChannel; }
        
    protected:
        
        CTraceChannel*      m_pChannel;
    };
}

#endif
