#include "TraceDataRepository.hpp"
#include "TraceInserter.hpp"


/********************************************************/
/*		Repository										*/
/********************************************************/


/**
 *
 */
TraceClientCore::CTraceDataRepository::CTraceDataRepository() :
m_TraceInserter(*this)
{
}


/**
 *
 */
TraceClientCore::CTraceDataRepository::~CTraceDataRepository()
{
}


/**
 *
 */
void TraceClientCore::CTraceDataRepository::Insert(TraceClientCore::CTraceData* pTraceData)
{
	m_refTracesList.InsertTail( pTraceData );
}


/**
 *
 */
TraceClientCore::CTraceData* TraceClientCore::CTraceDataRepository::Get( IteratorHandle hIterator )
{
	return m_refTracesList.Get(hIterator);
}


/**
 *
 */
TraceClientCore::CTraceData* TraceClientCore::CTraceDataRepository::Get( IteratorHandle hIterator ) const
{
	return m_refTracesList.Get(hIterator);
}


/**
 *
 */
size_t TraceClientCore::CTraceDataRepository::TracesCount() const
{
	return m_refTracesList->Size();
}


/**
 *
 */
TraceClientCore::ITraceDataRepository::IteratorHandle TraceClientCore::CTraceDataRepository::AllocIterator()
{
	return m_refTracesList->AllocIterator();
}


/**
 *
 */
TraceClientCore::ITraceDataRepository::IteratorHandle TraceClientCore::CTraceDataRepository::AllocIterator() const
{
	return m_refTracesList->AllocIterator();
}


/**
 *
 */
void TraceClientCore::CTraceDataRepository::ReleaseIterator( TraceClientCore::ITraceDataRepository::IteratorHandle& hIterator ) const
{
	m_refTracesList->ReleaseIterator(hIterator);
}


/**
 *
 */
void TraceClientCore::CTraceDataRepository::GetTailPos( TraceClientCore::ITraceDataRepository::IteratorHandle& hIterator )
{
	m_refTracesList->GetTailPos(hIterator);
}


/**
 *
 */
void TraceClientCore::CTraceDataRepository::GetTailPos( TraceClientCore::ITraceDataRepository::IteratorHandle& hIterator ) const
{
	m_refTracesList->GetTailPos(hIterator);
}


/**
 *
 */
void TraceClientCore::CTraceDataRepository::GetHeadPos( TraceClientCore::ITraceDataRepository::IteratorHandle& hIterator )
{
	m_refTracesList->GetHeadPos(hIterator);
}


/**
 *
 */
void TraceClientCore::CTraceDataRepository::GetHeadPos( TraceClientCore::ITraceDataRepository::IteratorHandle& hIterator ) const
{
	m_refTracesList->GetHeadPos(hIterator);

}


/**
 *
 */
void TraceClientCore::CTraceDataRepository::Clear()
{
	m_refTracesList->Clear();
}


/**
 *
 */
void TraceClientCore::CTraceDataRepository::Copy(	TraceClientCore::ITraceDataRepository::IteratorHandle hDst, 
													TraceClientCore::ITraceDataRepository::IteratorHandle hSrc ) const
{
	m_refTracesList->CopyIterator( hDst, hSrc );
}


/**
 *
 */
bool TraceClientCore::CTraceDataRepository::IsTail( TraceClientCore::ITraceDataRepository::IteratorHandle hIterator )
{
	return m_refTracesList->IsTail(hIterator);
}


/**
 *
 */
bool TraceClientCore::CTraceDataRepository::IsTail( TraceClientCore::ITraceDataRepository::IteratorHandle hIterator ) const
{
	return m_refTracesList->IsTail(hIterator);
}


/**
 *
 */
bool TraceClientCore::CTraceDataRepository::AreEqual(	TraceClientCore::ITraceDataRepository::IteratorHandle hPos1, 
														TraceClientCore::ITraceDataRepository::IteratorHandle hPos2 ) const
{
	return m_refTracesList->AreIteratorEqual( hPos1, hPos2 );
}


/**
 *
 */
bool TraceClientCore::CTraceDataRepository::IncrIterator( IteratorHandle hIterator )
{
	return m_refTracesList->IncrementIterator(hIterator);
}


/**
 *
 */
bool TraceClientCore::CTraceDataRepository::IncrIterator( IteratorHandle hIterator ) const
{
	return m_refTracesList->IncrementIterator(hIterator);
}


/**
 *
 */
bool TraceClientCore::CTraceDataRepository::DecrIterator( IteratorHandle hIterator )
{
	return m_refTracesList->DecrementIterator(hIterator);
}


/**
 *
 */
bool TraceClientCore::CTraceDataRepository::DecrIterator( IteratorHandle hIterator ) const
{
	return m_refTracesList->DecrementIterator(hIterator);
}
