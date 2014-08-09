//
//  TracesIterator.hpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2013-09-20.
//
//

#ifndef TraceClientCore_TracesIterator_hpp
#define TraceClientCore_TracesIterator_hpp

#include "TracesList.hpp"

namespace TraceClientCore
{
    /**
     *
     */
    class CTracesIterator
    {
        friend class CTracesList;
        
    public:
        CTracesIterator();
        CTracesIterator( CTracesList* pList );
        CTracesIterator( const CTracesIterator& iter );
        CTracesIterator( CTracesList* pList, const CTracesList::iterator& pos );
        virtual ~CTracesIterator();
        
        const CTracesIterator& operator = (const CTracesIterator& iter);
        
        const CTracesIterator& operator ++ ();
        const CTracesIterator& operator -- ();
        
        bool Valid() const;
        
        CTraceData* TraceData() const;
                
    protected:

        CTracesList*                m_pList;
        CTracesList::iterator       m_Pos;
    };
}


#endif
