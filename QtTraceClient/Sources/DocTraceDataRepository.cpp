#include "DocTraceDataRepository.hpp"


/**
 *
 */
CDocTraceDataRepository::CDocTraceDataRepository()
{
}


/**
 *
 */
CDocTraceDataRepository::~CDocTraceDataRepository()
{
}


/**
 *
 */
void CDocTraceDataRepository::Insert(const TraceClientCore::CTraceData* pTraceData)
{
    Nyx::CMemoryPool*    pMemPool = pTraceData->MemoryPool();
    CDocTraceData*      pDocTraceData = new (pMemPool)CDocTraceData(pMemPool, pTraceData);
    m_refTraces.InsertTail( pDocTraceData );
}


/**
 *
 */
const CDocTraceData* CDocTraceDataRepository::Get( IteratorHandle hIterator )
{
    return m_refTraces.Get(hIterator);
}


/**
 *
 */
const CDocTraceData* CDocTraceDataRepository::Get( IteratorHandle hIterator ) const
{
    return m_refTraces.Get(hIterator);
}


/**
 *
 */
size_t CDocTraceDataRepository::TracesCount() const
{
    return m_refTraces->Size();
}


/**
 *
 */
TraceClientCore::ITraceDataRepository::IteratorHandle CDocTraceDataRepository::AllocIterator()
{
    return m_refTraces->AllocIterator();
}


/**
 *
 */
TraceClientCore::ITraceDataRepository::IteratorHandle CDocTraceDataRepository::AllocIterator() const
{
    return m_refTraces->AllocIterator();
}


/**
 *
 */
void CDocTraceDataRepository::ReleaseIterator( TraceClientCore::ITraceDataRepository::IteratorHandle& hIterator ) const
{
    m_refTraces->ReleaseIterator(hIterator);
}


/**
 *
 */
void CDocTraceDataRepository::GetTailPos( TraceClientCore::ITraceDataRepository::IteratorHandle& hIterator )
{
    m_refTraces->GetTailPos(hIterator);
}


/**
 *
 */
void CDocTraceDataRepository::GetTailPos( TraceClientCore::ITraceDataRepository::IteratorHandle& hIterator ) const
{
    m_refTraces->GetTailPos(hIterator);
}


/**
 *
 */
void CDocTraceDataRepository::GetHeadPos( TraceClientCore::ITraceDataRepository::IteratorHandle& hIterator )
{
    m_refTraces->GetHeadPos(hIterator);
}


/**
 *
 */
void CDocTraceDataRepository::GetHeadPos( TraceClientCore::ITraceDataRepository::IteratorHandle& hIterator ) const
{
    m_refTraces->GetHeadPos(hIterator);
}


/**
 *
 */
void CDocTraceDataRepository::Clear()
{
    m_refTraces->Clear();
}


/**
 *
 */
void CDocTraceDataRepository::Copy(	TraceClientCore::ITraceDataRepository::IteratorHandle hDst,
                                                    TraceClientCore::ITraceDataRepository::IteratorHandle hSrc ) const
{
    m_refTraces->CopyIterator(hDst, hSrc);
}


/**
 *
 */
bool CDocTraceDataRepository::IsTail( TraceClientCore::ITraceDataRepository::IteratorHandle hIterator )
{
    return m_refTraces->IsTail(hIterator);
}


/**
 *
 */
bool CDocTraceDataRepository::IsTail( TraceClientCore::ITraceDataRepository::IteratorHandle hIterator ) const
{
    return m_refTraces->IsTail(hIterator);
}


/**
 *
 */
bool CDocTraceDataRepository::AreEqual(	TraceClientCore::ITraceDataRepository::IteratorHandle hPos1,
                                                        TraceClientCore::ITraceDataRepository::IteratorHandle hPos2 ) const
{
    return m_refTraces->AreIteratorEqual(hPos1, hPos2);
}


/**
 *
 */
bool CDocTraceDataRepository::IncrIterator( IteratorHandle hIterator )
{
    return m_refTraces->IncrementIterator(hIterator);
}


/**
 *
 */
bool CDocTraceDataRepository::IncrIterator( IteratorHandle hIterator ) const
{
    return m_refTraces->IncrementIterator(hIterator);
}


/**
 *
 */
bool CDocTraceDataRepository::DecrIterator( IteratorHandle hIterator )
{
    return m_refTraces->DecrementIterator(hIterator);
}


/**
 *
 */
bool CDocTraceDataRepository::DecrIterator( IteratorHandle hIterator ) const
{
    return m_refTraces->DecrementIterator(hIterator);
}
