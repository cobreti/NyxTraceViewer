#ifndef _TRACEDATAREPOSITORYLINKTODATAREPOSITORY_HPP_
#define _TRACEDATAREPOSITORYLINKTODATAREPOSITORY_HPP_

#include "TraceDataRepositoryLink.hpp"

namespace TraceClientCore
{
	class CTraceDataRepositoryLinkToDataRepository : public CTraceDataRepositoryLink
	{
	public:
		CTraceDataRepositoryLinkToDataRepository( const CTraceDataRepository& rSrcRepos, CTraceDataRepository& rDstRepos );
		virtual ~CTraceDataRepositoryLinkToDataRepository();

	protected:

		virtual void OnBeginUpdate();
		virtual void OnEndUpdate();
//		virtual void OnUpdate( const CTraceData* pTraceData );

	protected:

		CTraceDataRepository&				m_rDstRepos;
	};
}


#endif // _TRACEDATAREPOSITORYLINKTODATAREPOSITORY_HPP_
