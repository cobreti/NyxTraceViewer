#ifndef _APPCORESERVICES_HPP_
#define _APPCORESERVICES_HPP_

#include <Nyx.hpp>
#include <NyxRefCount_Impl.hpp>

#include "TracesPoolsCollection.hpp"
#include "TracesFeedersCollection.hpp"


DECLARE_OBJECTREF(CAppCoreServices)

/**
 *
 */
class CAppCoreServices : public Nyx::CRefCount_Impl<>
{
public:

	static CAppCoreServices& Instance();

public:
	CAppCoreServices();
	virtual ~CAppCoreServices();

	virtual Nyx::NyxResult Init();
	virtual Nyx::NyxResult Terminate();

	CTracesPoolsCollection&		TracesPools()		{ return m_TracesPools; }

	CTracesFeedersCollection&	Feeders()			{ return m_Feeders; }

protected:	// protected members

	CTracesPoolsCollection			m_TracesPools;
	CTracesFeedersCollection		m_Feeders;

	static CAppCoreServices*		s_pInstance;
};


#endif // _APPCORESERVICES_HPP_
