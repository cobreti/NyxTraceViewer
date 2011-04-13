#ifndef _DUMMY_TRACEFEEDER_HPP_
#define _DUMMY_TRACEFEEDER_HPP_

#pragma managed (push, off)

#include <Nyx.hpp>

#include "TracesFeeder.hpp"


/**
 *
 */
class CDummy_TraceFeeder : public CTracesFeeder
{
public: // public methods
	CDummy_TraceFeeder(const wchar_t* wszName);
	virtual ~CDummy_TraceFeeder();

	virtual void OnAddedToCollection();
	virtual void OnRemovedFromCollection();

protected: // protected methods

	virtual void Run();
	virtual void Stop();
	virtual void DispatchTrace();

protected: // protected members

	bool				m_bRunning;
	Nyx::CEventRef		m_refEvent;
	size_t				m_Counter;
	Nyx::CThreadRef		m_refThread;
};

#pragma managed(pop)


#endif // _DUMMY_TRACEFEEDER_HPP_
