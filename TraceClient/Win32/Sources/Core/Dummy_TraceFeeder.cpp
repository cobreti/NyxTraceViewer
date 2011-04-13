#pragma unmanaged

#include "Dummy_TraceFeeder.hpp"
#include "TraceData.hpp"


/**
 *
 */
CDummy_TraceFeeder::CDummy_TraceFeeder(const wchar_t* wszName) : CTracesFeeder(wszName),
m_bRunning(false),
m_Counter(0)
{
	m_refEvent = Nyx::CEvent::Alloc();
}


/**
 *
 */
CDummy_TraceFeeder::~CDummy_TraceFeeder()
{
}


/**
 *
 */
void CDummy_TraceFeeder::OnAddedToCollection()
{
	m_refThread = Nyx::CThread::Alloc();

	m_refThread->Start( new Nyx::CThreadDelegateNoRef<CDummy_TraceFeeder>(
							this,
							&CDummy_TraceFeeder::Run, &CDummy_TraceFeeder::Stop) );
}


/**
 *
 */
void CDummy_TraceFeeder::OnRemovedFromCollection()
{
	m_refThread->Stop();
	m_refThread = NULL;
}


/**
 *
 */
void CDummy_TraceFeeder::Run()
{
	m_bRunning = true;

	while (m_bRunning)
	{
		m_refEvent->WaitSignaled(100);

		if ( m_bRunning )
			DispatchTrace();
	}
}


/**
 *
 */
void CDummy_TraceFeeder::Stop()
{
	m_bRunning = false;
	m_refEvent->Signal(0);
}


/**
 *
 */
void CDummy_TraceFeeder::DispatchTrace()
{
	CTraceDataRef					refTraceData;
	Nyx::CStringFormaterRef			refStringFormater = Nyx::CStringFormater::Alloc(1024);

	++ m_Counter;

	refTraceData = new CTraceData();

	refStringFormater->Format(L"%08X", m_Counter);
	refTraceData->ThreadId() = Nyx::CString::Alloc( refStringFormater->GetBuffer() );

	refStringFormater->Format(L"%i", m_Counter);
	refTraceData->TickCount() = Nyx::CString::Alloc( refStringFormater->GetBuffer() );

	refStringFormater->Format(L"dummy feeder trace [%i]", m_Counter);
	refTraceData->Data() = Nyx::CString::Alloc(refStringFormater->GetBuffer());

	FeederLinks().Feed(refTraceData);
}
