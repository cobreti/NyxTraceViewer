#ifndef _TRACEDATAREPOSITERATOR_HPP_
#define _TRACEDATAREPOSITERATOR_HPP_

#pragma managed(push, off)

#include "TraceDataRepos.hpp"
#include <NyxMTObjAccessor.hpp>


/**
 *	\brief		TraceData Repository iterator methods interface
 */
class ITraceDataReposIterator
{
public:

};


/**
 *	\brief		TraceData Repository iterator
 */
class CTraceDataReposIterator : protected ITraceDataReposIterator
{
public:

	typedef		Nyx::CMTObjAccessor<CTraceDataReposIterator, ITraceDataReposIterator>		Accessor;
	friend class Nyx::CMTObjAccessor<CTraceDataReposIterator, ITraceDataReposIterator>;
	friend class CTraceDataRepos;

public:		// public methods
	CTraceDataReposIterator( const CTraceDataRepos& rRepos );
	virtual ~CTraceDataReposIterator();

	bool operator == ( const CTraceDataReposIterator& pos ) const		{ return m_Pos == pos.m_Pos; }
	bool operator != ( const CTraceDataReposIterator& pos ) const		{ return m_Pos != pos.m_Pos; }
	bool operator <  ( const CTraceDataReposIterator& pos ) const		{ return m_Index < pos.m_Index; }
	bool operator <= ( const CTraceDataReposIterator& pos ) const		{ return m_Index <= pos.m_Index; }
	bool operator >  ( const CTraceDataReposIterator& pos ) const		{ return m_Index > pos.m_Index; }
	bool operator >= ( const CTraceDataReposIterator& pos ) const		{ return m_Index >= pos.m_Index; }

	const CTraceDataReposIterator& operator = ( const CTraceDataReposIterator& pos );

protected:	// protected types

	typedef CTraceDataRepos::TraceDataList::const_iterator		TraceDataIterator;

protected:	// protected methods

	virtual bool MTLock();
	virtual bool MTTryLock();
	virtual void MTUnlock();

	CTraceDataReposIterator& operator ++ ();
	CTraceDataReposIterator& operator -- ();

protected:	// protected members

	const CTraceDataRepos&			m_rRepos;
	TraceDataIterator				m_Pos;
	size_t							m_Index;

};

#pragma managed(pop)

#endif // _TRACEDATAREPOSITERATOR_HPP_
