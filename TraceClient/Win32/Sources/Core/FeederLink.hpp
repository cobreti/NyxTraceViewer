#ifndef _FEEDERLINK_HPP_
#define _FEEDERLINK_HPP_

#include <Nyx.hpp>
#include <NyxRefCount_Impl.hpp>


DECLARE_OBJECTREF(CFeederLink)

class CTraceData;

/**
 *
 */
class CFeederLink : public Nyx::CRefCount_Impl<>
{
public: // public methods
	CFeederLink();
	virtual ~CFeederLink();

	virtual void Feed( CTraceData* pTraceData );

protected: // protected methods

	virtual void OnAddedToCollection();
	virtual void OnRemovedFromCollection();
};


#endif // _FEEDERLINK_HPP_
