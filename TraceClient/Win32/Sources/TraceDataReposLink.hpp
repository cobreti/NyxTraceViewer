#ifndef _TRACEDATAREPOSLINK_HPP_
#define _TRACEDATAREPOSLINK_HPP_

#include "TraceDataReposLinkBase.hpp"

class CTraceDataRepos;
class CUITraceDataRepository;
class CTraceDataReposIterator;


/**
 *
 */
class CTraceDataReposLink : public CTraceDataReposLinkBase
{
public:
	CTraceDataReposLink( CTraceDataRepos& rRepository, CUITraceDataRepository& rUIRepository );
	virtual ~CTraceDataReposLink();

	virtual bool Update();

protected:

	CTraceDataRepos&			m_rRepository;
	CUITraceDataRepository&		m_rUIRepository;
	CTraceDataReposIterator*	m_pSrcLastEndPos;
};


#endif // _TRACEDATAREPOSLINK_HPP_

