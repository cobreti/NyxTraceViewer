#ifndef _TRACEDATA_HPP_
#define _TRACEDATA_HPP_

#include <Nyx.hpp>
#include <NyxRefCount_Impl.hpp>

#pragma managed(push, off)

DECLARE_OBJECTREF(CTraceData);


/**
 *
 */
class CTraceData : public Nyx::CRefCount_Impl<>
{
public:
	CTraceData();
	virtual ~CTraceData();

	const Nyx::CStringRef&	ThreadId() const		{ return m_refThreadId; }
	Nyx::CStringRef&		ThreadId()				{ return m_refThreadId; }

	const Nyx::CStringRef&	TickCount() const		{ return m_refTickCount; }
	Nyx::CStringRef&		TickCount()				{ return m_refTickCount; }

	const Nyx::CStringRef&	Data() const			{ return m_refData; }
	Nyx::CStringRef&		Data()					{ return m_refData; }

protected:

	Nyx::CStringRef		m_refThreadId;
	Nyx::CStringRef		m_refTickCount;
	Nyx::CStringRef		m_refData;

private:

	// disable copy-constructor
	CTraceData(const CTraceData&);

	// disable operator =
	const CTraceData& operator = (const CTraceData&);
};


#pragma managed(pop)

#endif // _TRACEDATA_HPP_
