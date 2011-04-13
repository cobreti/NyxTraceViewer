#ifndef _TRACESPOOL_HPP_
#define _TRACESPOOL_HPP_

#include <Nyx.hpp>
#include <NyxRefCount_Impl.hpp>

#include "TraceDataRepos.hpp"


DECLARE_OBJECTREF(CTracesPool)


/**
 *
 */
class CTracesPool : public Nyx::CRefCount_Impl<>
{
public:
	CTracesPool(const wchar_t* wszName);
	virtual ~CTracesPool();

	virtual const Nyx::CStringRef Name() const;

	CTraceDataRepos&		TraceRepository() { return m_TracesRepository; }

protected:

	Nyx::CStringRef		m_refName;
	CTraceDataRepos		m_TracesRepository;
};


#endif // _TRACESPOOL_HPP_
