#include <Nyx.hpp>
#include <NyxClrDelegates.hpp>

#include "TracesViewController.hpp"
#include "UITraceDataRepository.hpp"
#include "AppCoreServices.hpp"
#include "UIRepositoryUpdater.hpp"
#include "TraceDataReposLink.hpp"
#include "TracesView.h"


/**
 *
 */
CTracesViewController::CTracesViewController(CTracesView^ View) :
m_TracesView(View),
m_pRepository(NULL),
m_pRepositoryUpdater(NULL)
{
	m_TracesView->HandleDestroyed += gcnew System::EventHandler( this, &CTracesViewController::OnViewClosed );

	m_pTracesPools = new CTracesPoolsCollection();

	CreateRepository();

	AddSrcPool(L"Default");
}


/**
 *
 */
CTracesViewController::~CTracesViewController()
{
	delete m_pRepository;
	delete m_pRepositoryUpdater;

	delete m_pTracesPools;

	Nyx::CTraceStream(0x0).Write(L"CTracesViewController destructor");
}


/**
 *
 */
void CTracesViewController::OnTest_UpdateUIRepos()
{
	CUIRepositoryUpdater::Accessor		UpdaterAccess(*m_pRepositoryUpdater);

	if ( UpdaterAccess )
		UpdaterAccess->Update();
}


/**
 *
 */
void CTracesViewController::CreateRepository()
{
	Nyx::CTraceStream(0x0).Write(L"Creating repository and adding callback");

	OnReposUpdate_Delegate^ pDelegate = gcnew OnReposUpdate_Delegate(this, &CTracesViewController::OnReposUpdate);

	Nyx::CDelegateBase<>*	pCallback = new Nyx::CClrDelegate<OnReposUpdate_Delegate>(pDelegate, m_TracesView);

	m_pRepository = new CUITraceDataRepository();
	m_pRepositoryUpdater = new CUIRepositoryUpdater(pCallback);

	{
		CUIRepositoryUpdater::Accessor		UpdaterAccess(*m_pRepositoryUpdater);

		if (UpdaterAccess)
			UpdaterAccess->Start();
	}
}


/**
 *
 */
void CTracesViewController::OnReposUpdate( void* pParam )
{
	if ( m_ReposUpdateDelegate != nullptr )
		m_ReposUpdateDelegate->Invoke(pParam);
}


/**
 *
 */
void CTracesViewController::AddSrcPool( const wchar_t* wszName )
{
	CTracesPool*		pPool = CAppCoreServices::Instance().TracesPools()[wszName];

	if ( pPool != NULL )
	{
		CUIRepositoryUpdater::Accessor		UpdaterAccess(*m_pRepositoryUpdater);

		if (UpdaterAccess)
			UpdaterAccess->Links().Add( new CTraceDataReposLink(pPool->TraceRepository(), *m_pRepository) );

		m_pTracesPools->Add(pPool);
	}
	else
	{
		MessageBox::Show( "traces pool not found", "Error",
			MessageBoxButtons::OK,
			MessageBoxIcon::Error );
	}
}


/**
 *
 */
void CTracesViewController::OnViewClosed( Object^ sender, EventArgs^ args )
{
	{
		CUIRepositoryUpdater::Accessor		UpdaterAccess(*m_pRepositoryUpdater);

		UpdaterAccess->Stop();
	}

	Nyx::CTraceStream(0x0).Write(L"View closed");
}
