#include "Application.hpp"
#include "TracePipeReceiver.hpp"


CApplication*		CApplication::s_pInstance = NULL;


/**
 *
 */
CApplication& CApplication::Instance()
{
	return *s_pInstance;
}


/**
 *
 */
CApplication::CApplication() :
m_pReceiver(NULL)
{
	s_pInstance = this;
}


/**
 *
 */
CApplication::~CApplication()
{
	s_pInstance = NULL;
}


/**
 *
 */
void CApplication::Init()
{
	NYXTRACE(0x0, L"TcpBridge starting");

	m_refTerminateEvent = Nyx::CEvent::Alloc();
	m_pReceiver = new CTracePipeReceiver("Test");

	SetCancelHandlers();
}


/**
 *
 */
void CApplication::Run()
{
	m_pReceiver->Start();
	m_refTerminateEvent->WaitSignaled();
}


/**
 *
 */
void CApplication::Terminate()
{
	m_pReceiver->Stop();
	delete m_pReceiver;

	NYXTRACE(0x0, L"TcpBridge closes");
}


/**
 *
 */
void CApplication::SignalTerminate()
{
	m_refTerminateEvent->Signal(0);
}

