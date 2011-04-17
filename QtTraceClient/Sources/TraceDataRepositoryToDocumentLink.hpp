#ifndef _TRACEDATAREPOSITORYTODOCUMENTLINK_HPP_
#define _TRACEDATAREPOSITORYTODOCUMENTLINK_HPP_

#include "TraceDataRepositoryLink.hpp"
#include "TraceDataRepository.hpp"

namespace TraceClientCore
{
    class CTraceDataRepository;
}

class CDocTraceDataRepository;

class CTraceDataRepositoryToDocumentLink : public TraceClientCore::CTraceDataRepositoryLink
{
public:
    CTraceDataRepositoryToDocumentLink(	const TraceClientCore::CTracesPool& rSrcPool );
    virtual ~CTraceDataRepositoryToDocumentLink();

	virtual bool Contains( const TraceClientCore::CTracesPool& rPool ) const;

protected:

	virtual void OnBeginUpdate();
	virtual void OnEndUpdate();

protected:

	const TraceClientCore::CTracesPool&								m_rSrcPool;
};


#endif // _TRACEDATAREPOSITORYTODOCUMENTLINK_HPP_
