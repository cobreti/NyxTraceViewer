#ifndef _TRACEDATAREPOSITORY_HPP_
#define _TRACEDATAREPOSITORY_HPP_

#include <Nyx.hpp>
#include <NyxOpaqueList.hpp>
#include <list>

#include "TraceData.hpp"
#include "RepositoryTraceInserter.hpp"


namespace TraceClientCore
{
	/**
	 *
	 */
	class ITraceDataRepository
	{
	public:

		typedef		Nyx::OpaqueListIterator			IteratorHandle;

	public:
		
		virtual void Insert(TraceClientCore::CTraceData* pTraceData) = 0;
		virtual CTraceData* Get( IteratorHandle hIterator ) = 0;
		virtual CTraceData* Get( IteratorHandle hIterator ) const = 0;
		virtual size_t TracesCount() const = 0;

		virtual IteratorHandle AllocIterator() = 0;
		virtual IteratorHandle AllocIterator() const = 0;
		virtual void ReleaseIterator( IteratorHandle& hIterator ) const = 0;
		virtual void GetTailPos( IteratorHandle& hIterator ) = 0;
		virtual void GetTailPos( IteratorHandle& hIterator ) const = 0;
		virtual void GetHeadPos( IteratorHandle& hIterator ) = 0;
		virtual void GetHeadPos( IteratorHandle& hIterator ) const = 0;
		virtual void Clear() = 0;
		virtual void Copy( IteratorHandle hDst, IteratorHandle hSrc ) const = 0;
		virtual bool IsTail( IteratorHandle hIterator ) = 0;
		virtual bool IsTail( IteratorHandle hIterator ) const = 0;
		virtual bool AreEqual( IteratorHandle hPos1, IteratorHandle hPos2 ) const = 0;
		virtual bool IncrIterator( IteratorHandle hIterator ) = 0;
		virtual bool IncrIterator( IteratorHandle hIterator ) const = 0;
		virtual bool DecrIterator( IteratorHandle hIterator ) = 0;
		virtual bool DecrIterator( IteratorHandle hIterator ) const = 0;
	};
	
	
	/**
	 *
	 */
	class CTraceDataRepository :  virtual public Nyx::CMTInterfaceAccess<	TraceClientCore::CTraceDataRepository,
																			TraceClientCore::ITraceDataRepository >
	{
		
	public: // public methods
		CTraceDataRepository();
		virtual ~CTraceDataRepository();
		
		CTraceInserter& TraceInserter()		{ return m_TraceInserter; }

	protected: // ITraceDataRepository methods

		virtual void Insert(TraceClientCore::CTraceData* pTraceData);
		virtual CTraceData* Get( IteratorHandle hIterator );
		virtual CTraceData* Get( IteratorHandle hIterator ) const;
		virtual size_t TracesCount() const;

		virtual IteratorHandle AllocIterator();
		virtual IteratorHandle AllocIterator() const;
		virtual void ReleaseIterator( IteratorHandle& hIterator ) const;
		virtual void GetTailPos( IteratorHandle& hIterator );
		virtual void GetTailPos( IteratorHandle& hIterator ) const;
		virtual void GetHeadPos( IteratorHandle& hIterator );
		virtual void GetHeadPos( IteratorHandle& hIterator ) const;
		virtual void Clear();
		virtual void Copy( IteratorHandle hDst, IteratorHandle hSrc ) const;
		virtual bool IsTail( IteratorHandle hIterator );
		virtual bool IsTail( IteratorHandle hIterator ) const;
		virtual bool AreEqual( IteratorHandle hPos1, IteratorHandle hPos2 ) const;
		virtual bool IncrIterator( IteratorHandle hIterator );
		virtual bool IncrIterator( IteratorHandle hIterator ) const;
		virtual bool DecrIterator( IteratorHandle hIterator );
		virtual bool DecrIterator( IteratorHandle hIterator ) const;


	protected: // protected methods
	
//		virtual void OnMTLocking();
//		virtual void OnMTUnlocking();

	protected: // protected members
			
		Nyx::TOpaqueListRef<TraceClientCore::CTraceData*>		m_refTracesList;
		
		CRepositoryTraceInserter								m_TraceInserter;
	};	
}


#endif // _TRACEDATAREPOSITORY_HPP_
