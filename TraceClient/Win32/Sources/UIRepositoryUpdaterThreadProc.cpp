#include "UIRepositoryUpdaterThreadProc.hpp"
#include "UIRepositoryUpdater.hpp"


/**
 *
 */
CUIRepositoryUpdaterThreadProc::CUIRepositoryUpdaterThreadProc( CUIRepositoryUpdater& rUpdater ) :
m_rUpdater(rUpdater),
m_bRunning(true)
{
	m_refEvent = Nyx::CEvent::Alloc();
}


/**
 *
 */
CUIRepositoryUpdaterThreadProc::~CUIRepositoryUpdaterThreadProc()
{
}


/**
 *
 */
void CUIRepositoryUpdaterThreadProc::Run()
{
	m_bRunning = true;

	while ( m_bRunning )
	{
		m_refEvent->WaitSignaled(250);

		if ( m_bRunning )
		{
			CUIRepositoryUpdater::Accessor		UpdaterAccess(m_rUpdater, Nyx::eMTLM_Trylock);

			if ( UpdaterAccess.Locked() )
				UpdaterAccess->Update();
		}
	}
}


/**
 *
 */
void CUIRepositoryUpdaterThreadProc::Stop()
{
	m_bRunning = false;
	m_refEvent->Signal(0);
}

