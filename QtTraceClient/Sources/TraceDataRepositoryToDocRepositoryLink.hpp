#ifndef _TRACEDATAREPOSITORYTODOCREPOSITORYLINK_HPP_
#define _TRACEDATAREPOSITORYTODOCREPOSITORYLINK_HPP_

#include "TraceDataRepositoryLink.hpp"
#include "TraceDataRepository.hpp"
#include "DocTraceDataRepository.hpp"

namespace TraceClientCore
{
    class CTraceDataRepository;
}

class CDocTraceDataRepository;

class CTraceDataRepositoryToDocRepositoryLink : public TraceClientCore::CTraceDataRepositoryLink
{
public:
	CTraceDataRepositoryToDocRepositoryLink(	const TraceClientCore::CTracesPool& rSrcPool,
												const TraceClientCore::CTraceDataRepository& rSrcRepos,
                                                CDocTraceDataRepository& rDstRepos );
    virtual ~CTraceDataRepositoryToDocRepositoryLink();

	virtual bool Contains( const TraceClientCore::CTracesPool& rPool ) const;

protected:

	virtual void OnBeginUpdate();
	virtual void OnEndUpdate();
    virtual void OnUpdate( const TraceClientCore::CTraceData* pTraceData );

protected:

	const TraceClientCore::CTracesPool&								m_rSrcPool;
    CDocTraceDataRepository&                                        m_rDstRepos;

	CDocTraceDataRepository::Accessor								m_ReposAccessor;

    size_t                                                          m_Count;
};


#endif // _TRACEDATAREPOSITORYTODOCREPOSITORYLINK_HPP_
