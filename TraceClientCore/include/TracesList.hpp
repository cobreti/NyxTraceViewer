//
//  TracesList.hpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2013-09-20.
//
//

#ifndef _TRACESLIST_HPP_
#define _TRACESLIST_HPP_

#include <Nyx.hpp>
#include "TraceData.hpp"

#include <list>

namespace TraceClientCore
{
    class CTracesIterator;
    
    /**
     *
     */
    class CTracesList : protected std::list<CTraceData*>
    {
        friend class CTracesIterator;
        
    public:
        CTracesList();
        virtual ~CTracesList();
        
        CTracesIterator FirstPos();
        CTracesIterator LastPos();
        
    protected:
        
        Nyx::CMutexRef      m_refMutex;
    };
}

#endif // _TRACESLIST_HPP_
