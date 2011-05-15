#include "TraceFeeder.hpp"
#include "TraceInserter.hpp"


/**
 *
 */
TraceClientCore::CTraceFeeder::CTraceFeeder( CTracesPool* pOwnerPool ) :
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
void TraceClientCore::CTraceFeeder::SetOwnerPool(TraceClientCore::CTracesPool *pOwnerPool)
{
    m_pOwnerPool = pOwnerPool;
}

