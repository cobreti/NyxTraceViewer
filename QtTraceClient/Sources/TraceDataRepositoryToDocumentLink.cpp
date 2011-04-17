#include "TraceDataRepositoryToDocumentLink.hpp"
#include "TracesPool.hpp"

/**
 *
 */
CTraceDataRepositoryToDocumentLink::CTraceDataRepositoryToDocumentLink(	const TraceClientCore::CTracesPool& rSrcPool ) :
TraceClientCore::CTraceDataRepositoryLink(rSrcPool.Repository()),
m_rSrcPool(rSrcPool)
{
}


/**
 *
 */
CTraceDataRepositoryToDocumentLink::~CTraceDataRepositoryToDocumentLink()
{
}


/**
 *
 */
bool CTraceDataRepositoryToDocumentLink::Contains( const TraceClientCore::CTracesPool& rPool ) const
{
	return (&rPool == &m_rSrcPool);
}


/**
 *
 */
void CTraceDataRepositoryToDocumentLink::OnBeginUpdate()
{
}


/**
 *
 */
void CTraceDataRepositoryToDocumentLink::OnEndUpdate()
{
}
