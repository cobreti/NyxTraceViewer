//
//  TracesList.cpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2013-09-20.
//
//

#include "TracesList.hpp"
#include "TracesIterator.hpp"

namespace TraceClientCore
{
    /**
     *
     */
    CTracesList::CTracesList()
    {
        m_refMutex = Nyx::CMutex::Alloc();
    }
    
    
    /**
     *
     */
    CTracesList::~CTracesList()
    {
    }

    
    /**
     *
     */
    CTracesIterator CTracesList::FirstPos()
    {
        return CTracesIterator(this, begin());
    }
    
    
    /**
     *
     */
    CTracesIterator CTracesList::LastPos()
    {
        iterator        pos = end();
        
        if ( !empty() )
        {
            -- pos;
            return CTracesIterator(this, pos);
        }

        return CTracesIterator();
    }
}