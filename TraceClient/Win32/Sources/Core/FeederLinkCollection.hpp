#ifndef _FEEDERLINKCOLLECTION_HPP_
#define _FEEDERLINKCOLLECTION_HPP_

#include "FeederLink.hpp"

#include <list>

/**
 *
 */
class CFeederLinkCollection : public CFeederLink
{
public: // public methods
	CFeederLinkCollection();
	virtual ~CFeederLinkCollection();

	virtual void Add( CFeederLink* pFeederLink );
	virtual void Remove( CFeederLink* pFeederLink );

	virtual void Feed( CTraceData* pTraceData );

protected: // protected types

	typedef		std::list<CFeederLinkRef>			FeederLinkList;

protected: // protected members

	FeederLinkList		m_FeederLinks;
};


#endif // _FEEDERLINKCOLLECTION_HPP_
