#ifndef _TRACEDATAREPOSLINKBASE_HPP_
#define _TRACEDATAREPOSLINKBASE_HPP_

#include <Nyx.hpp>
#include <NyxRefCount_Impl.hpp>

DECLARE_OBJECTREF(CTraceDataReposLinkBase)

class CTraceDataReposLinkBase : public Nyx::CRefCount_Impl<>
{
public:
	CTraceDataReposLinkBase();
	virtual ~CTraceDataReposLinkBase();

	virtual bool Update();
};


#endif // _TRACEDATAREPOSLINKBASE_HPP_
