#ifndef _TRACESPOOLSCOLLECTION_HPP_
#define _TRACESPOOLSCOLLECTION_HPP_


#include "TracesPool.hpp"

#include <map>


/**
 *
 */
class CTracesPoolsCollection
{
public:	// public methods
	CTracesPoolsCollection();
	virtual ~CTracesPoolsCollection();

	virtual void Add( CTracesPool* pPool );

	CTracesPool* operator [] ( const wchar_t* wszPoolName );

protected: // protected types

	typedef		std::map<const Nyx::CTString, CTracesPoolRef>		TracesPoolsTable;

protected: // protected members

	TracesPoolsTable		m_TracesPools;
};


#endif // _TRACESPOOLSCOLLECTION_HPP_
