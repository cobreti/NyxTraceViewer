#ifndef _PIPETRACEFEEDERS_HPP_
#define _PIPETRACEFEEDERS_HPP_

#include <Nyx.hpp>
#include <NyxNet.hpp>

#include "TracesFeeder.hpp"
#include "PipeDataReceiver.hpp"


/**
 *
 */
class CPipeTraceFeeder : public CTracesFeeder
{
public: // public methods
	CPipeTraceFeeder(const wchar_t* wszName);
	virtual ~CPipeTraceFeeder();

	virtual void OnAddedToCollection();
	virtual void OnRemovedFromCollection();

	virtual bool MTCancelLock() const;

protected: // protected members

	Nyx::CAnsiStringRef					m_refPipeName;
	NyxNet::CNxConnectionRef			m_refConnection;
	CPipeDataReceiver*					m_pPipeDataReceiver;
	NyxNet::CPipeServerRef				m_refPipeServer;
	bool								m_bRunning;
};


#endif // _PIPETRACEFEEDERS_HPP_
