#include "UIRepositoryUpdater.hpp"
#include "UIRepositoryUpdaterThreadProc.hpp"

/**
 *
 */
CUIRepositoryUpdater::CUIRepositoryUpdater( Nyx::CDelegateBase<>* pUICallback ) :
m_refUICallback(pUICallback)
{
}


/**
 *
 */
CUIRepositoryUpdater::~CUIRepositoryUpdater()
{
}


/**
 *
 */
CTraceDataReposLinksCollection& CUIRepositoryUpdater::Links()
{
	return m_Links;
}


/**
 *
 */
void CUIRepositoryUpdater::Update()
{
	if ( m_Links.Update() && m_refUICallback.Valid() )
	{
		m_refUICallback->Invoke();
	}
}


/**
 *
 */
void CUIRepositoryUpdater::Start()
{
	m_refThread = Nyx::CThread::Alloc();
	m_refThread->Start( new CUIRepositoryUpdaterThreadProc(*this) );
}


/**
 *
 */
void CUIRepositoryUpdater::Stop()
{
	if ( m_refThread.Valid() )
	{
		m_refThread->Stop();
		m_refThread = NULL;
	}
}

