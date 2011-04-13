#ifndef _REPOSITORYTRACEINSERTER_HPP_
#define _REPOSITORYTRACEINSERTER_HPP_

#include "TraceInserter.hpp"


namespace TraceClientCore
{
    class CTraceDataRepository;

    class CRepositoryTraceInserter : public CTraceInserter
    {
    public:
		CRepositoryTraceInserter(CTraceDataRepository& rRepository);
		virtual ~CRepositoryTraceInserter();
		
		virtual void Insert( CTraceData* pTraceData );
		
	protected:
        
		CTraceDataRepository&		m_rRepository;
    };
}



#endif // _REPOSITORYTRACEINSERTER_HPP_
