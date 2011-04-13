#ifndef _TRACESFEEDERSCOLLECTION_HPP_
#define _TRACESFEEDERSCOLLECTION_HPP_

#include "TracesFeeder.hpp"

#include <map>


/**
 *
 */
class CTracesFeedersCollection
{
public:	// public methods
	CTracesFeedersCollection();
	virtual ~CTracesFeedersCollection();

	virtual void Add( CTracesFeeder* pFeeder );
	virtual void Remove( CTracesFeeder* pFeeder );
	virtual void Clear();

	virtual CTracesFeeder* Get( const wchar_t* wszName );

protected: // protected types

	typedef		std::map<Nyx::CTString, CTracesFeederRef>			TracesFeedersTable;

protected: // protected members

	TracesFeedersTable		m_TracesFeeders;
};


#endif // _TRACESFEEDERSCOLLECTION_HPP_
