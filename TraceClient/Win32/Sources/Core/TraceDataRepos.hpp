#ifndef _TRACEDATAREPOS_HPP_
#define _TRACEDATAREPOS_HPP_

#pragma managed(push, off)

#include <list>
#include <NyxMutex.hpp>
#include <NyxMTObjAccessor.hpp>
#include <NyxMTInterfaceAccess.hpp>

#include "TraceData.hpp"


class CTraceDataReposIterator;


/**
 *	\brief		TraceData methods interface
 */
class ITraceDataRepos
{
public:

	virtual size_t Count() const = 0;
	virtual void Add( CTraceData* pTraceData ) = 0;

	virtual const CTraceDataReposIterator& HeadPos() const = 0;
	virtual const CTraceDataReposIterator& TailPos() const = 0;
	virtual bool IsEmpty() const = 0;

	virtual CTraceData* Get( const CTraceDataReposIterator& pos ) const = 0;
};


/**
 *	\brief		TraceData Repository
 */
class CTraceDataRepos : public Nyx::CMTInterfaceAccess<CTraceDataRepos, ITraceDataRepos>
{
	friend class CTraceDataReposIterator;

public: // public methods
	CTraceDataRepos();
	virtual ~CTraceDataRepos();

protected: // protected types

	/**
	 *	\brief		List of tracedata
	 */
	typedef		std::list<CTraceDataRef>		TraceDataList;

protected: // protected methods

	virtual void OnMTLastWriteUnlock();

	virtual size_t Count() const;
	virtual void Add( CTraceData* pTraceData );

	virtual const CTraceDataReposIterator& HeadPos() const;
	virtual const CTraceDataReposIterator& TailPos() const;
	virtual bool IsEmpty() const;

	virtual CTraceData* Get( const CTraceDataReposIterator& pos ) const;

protected: // protected members

	TraceDataList							m_TracesData;
	CTraceDataReposIterator*				m_pHeadPos;
	CTraceDataReposIterator*				m_pTailPos;
	Nyx::UInt32								m_AddedTraces;

private:
	
	// disable copy-constructor
	CTraceDataRepos(const CTraceDataRepos&);

	// disable operator = 
	const CTraceDataRepos& operator = (const CTraceDataRepos&);

};

#pragma managed(pop)

#endif // _TRACEDATAREPOS_HPP_
