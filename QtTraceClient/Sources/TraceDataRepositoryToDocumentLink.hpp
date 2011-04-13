#ifndef _TRACEDATAREPOSITORYTODOCUMENTLINK_HPP_
#define _TRACEDATAREPOSITORYTODOCUMENTLINK_HPP_

#include "TraceDataRepositoryLink.hpp"
#include "TraceDataRepository.hpp"
#include "DocTraceDataRepository.hpp"

namespace TraceClientCore
{
    class CTraceDataRepository;
}

class CDocTraceDataRepository;

class CTraceDataRepositoryToDocumentLink : public TraceClientCore::CTraceDataRepositoryLink
{
public:
    CTraceDataRepositoryToDocumentLink(	const TraceClientCore::CTracesPool& rSrcPool,
                                                const TraceClientCore::CTraceDataRepository& rSrcRepos,
                                                CDocTraceDataRepository& rDstRepos );
    virtual ~CTraceDataRepositoryToDocumentLink();

	virtual bool Contains( const TraceClientCore::CTracesPool& rPool ) const;
//    virtual bool Update(TraceClientCore::CTraceInserter *pTraceInserter);

protected:

	virtual void OnBeginUpdate();
	virtual void OnEndUpdate();
//    virtual void OnUpdate( const TraceClientCore::CTraceData* pTraceData );

protected:

	const TraceClientCore::CTracesPool&								m_rSrcPool;
    CDocTraceDataRepository&                                        m_rDstRepos;

	CDocTraceDataRepository::Accessor								m_ReposAccessor;

    size_t                                                          m_Count;
};


#endif // _TRACEDATAREPOSITORYTODOCUMENTLINK_HPP_
