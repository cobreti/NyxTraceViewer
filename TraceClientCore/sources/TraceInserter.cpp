#include "TraceInserter.hpp"
#include "TraceDataRepository.hpp"


/**
 *
 */
TraceClientCore::CTraceInserter::CTraceInserter( TraceClientCore::CTraceDataRepository& rRepository ) :
m_rRepository(rRepository)
{
}


/**
 *
 */
TraceClientCore::CTraceInserter::~CTraceInserter()
{
}


/**
 *
 */
void TraceClientCore::CTraceInserter::Insert( TraceClientCore::CTraceData* pTraceData )
{
	CTraceDataRepository::Accessor		RepoAccess(m_rRepository);
	
	if ( RepoAccess )
	{
		RepoAccess->Insert(pTraceData);
	}
}
