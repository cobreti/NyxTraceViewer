#ifndef _TRACEDATAREPOSLINKCOLLECTION_HPP_
#define _TRACEDATAREPOSLINKCOLLECTION_HPP_

#include "TraceDataReposLinkBase.hpp"

#include <list>

/**
 *
 */
class CTraceDataReposLinksCollection : public CTraceDataReposLinkBase
{
public:	// public methods
	CTraceDataReposLinksCollection();
	virtual ~CTraceDataReposLinksCollection();

	virtual bool Update();

	virtual void Add( CTraceDataReposLinkBase* pLink );

protected:	// protected types

	typedef		std::list<CTraceDataReposLinkBaseRef>			TDRLinksList;

protected:	// protected members

	TDRLinksList		m_Links;
};


#endif // _TRACEDATAREPOSLINKCOLLECTION_HPP_
