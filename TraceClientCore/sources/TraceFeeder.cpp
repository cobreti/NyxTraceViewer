#include "TraceFeeder.hpp"
#include "TraceInserter.hpp"


/**
 *
 */
TraceClientCore::CTraceFeeder::CTraceFeeder( CTracesPool* pOwnerPool, TraceClientCore::CTraceInserter* pTraceInserter ) :
m_pTraceInserter(pTraceInserter),
m_pOwnerPool(pOwnerPool)
{
}


/**
 *
 */
TraceClientCore::CTraceFeeder::~CTraceFeeder()
{
}


/**
 *
 */
void TraceClientCore::CTraceFeeder::SetTraceInserter( CTraceInserter* pTraceInserter )
{
	m_pTraceInserter = pTraceInserter;
}


/**
 *
 */
void TraceClientCore::CTraceFeeder::SetOwnerPool(TraceClientCore::CTracesPool *pOwnerPool)
{
    m_pOwnerPool = pOwnerPool;
}