//
//  MultiViewTracesIterator.hpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2013-09-20.
//
//

#ifndef TraceClientCore_MultiViewTracesIterator_hpp
#define TraceClientCore_MultiViewTracesIterator_hpp

#include <Nyx.hpp>

#include "TracesIterator.hpp"

#include <map>

namespace TraceClientCore
{
    class CTracesView;
    class CTracesGroup;
    
    
    /**
     *
     */
    class CMultiViewTracesIterator
    {
        friend class CTracesGroup;
        
    public:
        CMultiViewTracesIterator();
        CMultiViewTracesIterator( const CMultiViewTracesIterator& iter );
        virtual ~CMultiViewTracesIterator();
        
        const CMultiViewTracesIterator& operator = (const CMultiViewTracesIterator& iter);
        
        bool Valid() const;
        
        const CMultiViewTracesIterator& operator ++ ();
        const CMultiViewTracesIterator& operator -- ();
        
        CTraceData* TraceData() const;
        
    protected:
        
        typedef     std::map<CTracesView*, CTracesIterator>     TViewIteratorMap;
        
    protected:
        
        TViewIteratorMap            m_Iterators;
        
        CTracesIterator             m_CurrentPos;
        CTracesView*                m_pCurrentView;
        CTracesGroup*               m_pTracesGroup;
    };
}



#endif
