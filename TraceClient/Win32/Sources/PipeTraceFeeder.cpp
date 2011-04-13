#include "PipeTraceFeeder.hpp"


/**
 *
 */
CPipeTraceFeeder::CPipeTraceFeeder(const wchar_t* wszName) : 
CTracesFeeder(wszName),
m_pPipeDataReceiver(NULL),
m_bRunning(true)
{
	Nyx::CStringFormaterRef		refStrFormater = Nyx::CStringFormater::Alloc(1024);

	refStrFormater->Format(L"%S_%s", wszName, "Pipe");

	m_refPipeName = Nyx::CAnsiString::Alloc();
	m_refPipeName->Set( refStrFormater->GetBuffer() );
}


/**
 *
 */
CPipeTraceFeeder::~CPipeTraceFeeder()
{
}


/**
 *
 */
void CPipeTraceFeeder::OnAddedToCollection()
{
	m_pPipeDataReceiver = new CPipeDataReceiver(*this);
	m_refConnection = NyxNet::CNxConnection::Alloc();
	m_refConnection->SetConnectionHandler(m_pPipeDataReceiver);

	m_refPipeServer = NyxNet::CPipeServer::Alloc();
	m_refPipeServer->Create( m_refPipeName->CStr(), 4096, m_refConnection );
	m_refPipeServer->Start();
}


/**
 *
 */
void CPipeTraceFeeder::OnRemovedFromCollection()
{
	m_bRunning = false;
	m_refPipeServer->Stop();
	m_refPipeServer = NULL;
	m_refConnection  = NULL;

	delete m_pPipeDataReceiver;
}


/**
 *
 */
bool CPipeTraceFeeder::MTCancelLock() const
{
	return !m_bRunning;
}
