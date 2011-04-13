#include "TraceDataRepositoryLinkToDataRepository.hpp"


namespace TraceClientCore
{
	/**
	 *
	 */
	CTraceDataRepositoryLinkToDataRepository::CTraceDataRepositoryLinkToDataRepository( const CTraceDataRepository& rSrcRepos, CTraceDataRepository& rDstRepos ) :
	CTraceDataRepositoryLink( rSrcRepos ),
	m_rDstRepos(rDstRepos)
	{
	}


	/**
	 *
	 */
	CTraceDataRepositoryLinkToDataRepository::~CTraceDataRepositoryLinkToDataRepository()
	{
	}


	/**
	 *
	 */
	void CTraceDataRepositoryLinkToDataRepository::OnBeginUpdate()
	{
	}


	/**
	 *
	 */
	void CTraceDataRepositoryLinkToDataRepository::OnEndUpdate()
	{
	}


	/**
	 *
	 */
//	void CTraceDataRepositoryLinkToDataRepository::OnUpdate(const TraceClientCore::CTraceData* pTraceData)
//	{
//	}

}
