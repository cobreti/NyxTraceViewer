#ifndef _TRACEDATAREPOSFEEDERLINK_HPP_
#define _TRACEDATAREPOSFEEDERLINK_HPP_


#include "FeederLink.hpp"

class CTraceDataRepos;


/**
 *
 */
class CTraceDataReposFeederLink : public CFeederLink
{
public: // public methods
	CTraceDataReposFeederLink( CTraceDataRepos& rRepos );
	virtual ~CTraceDataReposFeederLink();

	virtual void Feed( CTraceData* pTraceData );

protected: // protected methods

	CTraceDataRepos&		m_rRepos;
};



#endif // _TRACEDATAREPOSFEEDERLINK_HPP_
