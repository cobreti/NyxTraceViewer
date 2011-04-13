#include "TraceDataReposFeederLink.hpp"

#include "TraceDataRepos.hpp"


/**
 *
 */
CTraceDataReposFeederLink::CTraceDataReposFeederLink( CTraceDataRepos& rRepos ) :
m_rRepos(rRepos)
{
}


/**
 *
 */
CTraceDataReposFeederLink::~CTraceDataReposFeederLink()
{
}


/**
 *
 */
void CTraceDataReposFeederLink::Feed(CTraceData *pTraceData)
{
	CTraceDataRepos::Accessor		ReposAccess(m_rRepos);

	if ( ReposAccess )
		ReposAccess->Add(pTraceData);
}
