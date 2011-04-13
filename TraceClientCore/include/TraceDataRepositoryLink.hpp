#ifndef _TRACEDATAREPOSITORYLINK_HPP_
#define _TRACEDATAREPOSITORYLINK_HPP_

#include "TraceDataRepositoryLinkBase.hpp"
#include "TraceDataRepository.hpp"

namespace TraceClientCore
{
	class CTraceDataRepository;

	class CTraceDataRepositoryLink : public CTraceDataRepositoryLinkBase
	{
	public:
		CTraceDataRepositoryLink(	const CTraceDataRepository& rSrcRepos );
		virtual ~CTraceDataRepositoryLink();

		virtual bool Update(CTraceInserter* pTraceInserter);

	protected:

		virtual void OnBeginUpdate();
		virtual void OnEndUpdate();
//		virtual void OnUpdate( const CTraceData* refTraceData );

	protected:
	
		const CTraceDataRepository&						m_rSrcRepos;
		
		ITraceDataRepository::IteratorHandle			m_hLastEndPos;
	};
}


#endif // _TRACEDATAREPOSITORYLINK_HPP_
