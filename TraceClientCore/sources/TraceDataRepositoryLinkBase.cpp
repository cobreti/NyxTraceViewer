#include "TraceDataRepositoryLinkBase.hpp"


/**
 *
 */
TraceClientCore::CTraceDataRepositoryLinkBase::CTraceDataRepositoryLinkBase() :
m_bUpdateCancelled(false)
{
}


/**
 *
 */
TraceClientCore::CTraceDataRepositoryLinkBase::~CTraceDataRepositoryLinkBase()
{
}


/**
 *
 */
bool TraceClientCore::CTraceDataRepositoryLinkBase::Update(CTraceInserter* pTraceInserter)
{
	return false;
}


/**
 *
 */
void TraceClientCore::CTraceDataRepositoryLinkBase::CancelUpdate()
{
	m_bUpdateCancelled = true;
}


/**
 *
 */
bool TraceClientCore::CTraceDataRepositoryLinkBase::Contains( const CTracesPool& rPool ) const
{
	return false;
}
