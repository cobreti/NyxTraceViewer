#ifndef _PIPETRACEFEEDER_HPP_
#define _PIPETRACEFEEDER_HPP_

#include "TraceFeeder.hpp"
#include "TraceNxStreamReader.hpp"

#include <Nyx.hpp>
#include <NyxNet.hpp>

namespace TraceClientCore
{
    class CTraceData;
    
	class CPipeTraceFeeder :	public CTraceFeeder,
								public NyxNet::INxConnectionHandler
	{
	public:
		CPipeTraceFeeder( CTraceChannel* pChannel );
		virtual ~CPipeTraceFeeder();
		
		virtual void Start();
		virtual void Stop();
		virtual bool IsRunning() const;
		
		// INxConnectionHandler
		virtual void HandleStream( NyxNet::INxStreamRW& rStream );
		virtual Nyx::NyxResult OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::INxConnectionHandler*& pCloneHandler );
		virtual void OnConnectionTerminated( NyxNet::IConnection* pConnection );

	protected:
	
		NyxNet::CNxConnectionRef	m_refNxConnection;
		NyxNet::CPipeServerRef		m_refServer;
		Nyx::TBuffer<Nyx::Byte>		m_ReadBuffer;
		Nyx::CAString				m_Name;
        Nyx::Int32                  m_TracesCount;
        CTraceData*                 m_pLastTrace;
        CTraceNxStreamReader        m_TraceReader;
	};
}


#endif // _PIPETRACEFEEDER_HPP_
