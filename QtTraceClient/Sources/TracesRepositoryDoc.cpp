#include "TracesRepositoryDoc.hpp"
#include "TracesView.h"

#include "TraceDataRepositoryToDocRepositoryLink.hpp"
#include "DocObserverNotificationsHandler.hpp"
#include "TracesPool.hpp"

/**
 *
 */
CTracesRepositoryDoc::CTracesRepositoryDoc(QWidget* pDefaultViewsParentWindow, const QString& name) :
m_pRepository(NULL),
m_pDefaultViewsParentWindow(pDefaultViewsParentWindow),
m_Name(name)
{
	m_pRepository = new CDocTraceDataRepository();
}


/**
 *
 */
CTracesRepositoryDoc::~CTracesRepositoryDoc()
{
	delete m_pRepository;
	Nyx::CTraceStream(0x0).Write(L"CTracesRepositoryDoc::~CTracesRepositoryDoc");
}


/**
 *
 */
void CTracesRepositoryDoc::Init()
{
    CViewItemSettings*      pSetting = NULL;
    QFont*                  pFont = new QFont("Courier New", 10);

    ViewItemsSettings().GetDefault()->SetFont( pFont );

//    ViewItemsSettings().GetDefault()->SetMargins( CViewItemMargins(5, 0, 5, 0)  );

    pSetting = new CViewItemSettings();
    pSetting->SetFont( new QFont("Courier New", 10 ) );
//    pSetting->SetMargins( CViewItemMargins(5, 0, 5, 0) );
    ViewItemsSettings().Add( CViewItemPainter::ePId_TickCount, pSetting );

    pSetting = new CViewItemSettings();
    pSetting->SetFont( new QFont("Courier New", 10 ) );
//    pSetting->SetMargins( CViewItemMargins(5, 0, 5, 0) );
    ViewItemsSettings().Add( CViewItemPainter::ePId_ThreadId, pSetting );

    pSetting = new CViewItemSettings();
    pSetting->SetFont( new QFont("Courier New", 9, 2) );
    ViewItemsSettings().Add( CViewItemPainter::ePId_Header, pSetting );

    TraceClientCore::CRepositoryObserver::Accessor       ROAccess(m_RepositoryObserver);

	ROAccess->NotificationsHandler() = new CDocObserverNotificationsHandler(*this);
    ROAccess->Start();
}


/**
 *
 */
void CTracesRepositoryDoc::Destroy()
{
	{
		TraceClientCore::CRepositoryObserver::Accessor		ROAccess(m_RepositoryObserver);

		ROAccess->Stop();
		ROAccess->NotificationsHandler() = NULL;

		while ( !m_UsedLinks.empty() )
		{
			TraceClientCore::CTraceDataRepositoryLinkBaseRef	refLink = m_UsedLinks.front();
			ROAccess->Links().Remove( refLink );
			m_UsedLinks.pop_front();
		}

	}

	Nyx::CTraceStream(0x0).Write(L"before clearing the repository");

	{
		CDocTraceDataRepository::Accessor		ReposAccess(*m_pRepository);

		ReposAccess->Clear();
	}

	while ( !m_Views.empty() )
	{
		m_Views.front()->close();
		delete m_Views.front();
		m_Views.pop_front();
	}
}


/**
 *
 */
CTracesView* CTracesRepositoryDoc::CreateView(QWidget* pParent)
{
    CTracesView*        pView = new CTracesView(*this, pParent);

	pView->Settings().ViewItemsSettings() = ViewItemsSettings();
    m_Views.push_back(pView);
    pView->setParent(NULL/*m_pDefaultViewsParentWindow*/, Qt::Window);
    //pView->show();

    OnNewTraceItems();

    return pView;
}


/**
 *
 */
void CTracesRepositoryDoc::GetViews( CTracesRepositoryDoc::TracesViewList& ViewsList ) const
{
	TracesViewList::const_iterator		pos = m_Views.begin();

	while ( pos != m_Views.end() )
	{
		ViewsList.push_back(*pos);
		++ pos;
	}
}


/**
 *
 */
void CTracesRepositoryDoc::AddRepositorySrc( TraceClientCore::CTracesPool& rSrcPool )
{
    TraceClientCore::CRepositoryObserver::Accessor              ROAccess(m_RepositoryObserver);
	CTraceDataRepositoryToDocRepositoryLink*                    pLink = new CTraceDataRepositoryToDocRepositoryLink(rSrcPool, rSrcPool.Repository(), *m_pRepository);

    ROAccess->Links().Add(pLink);

	m_UsedLinks.push_back(pLink);
}


/**
 *
 */
void CTracesRepositoryDoc::RemoveRepositorySrc( TraceClientCore::CTracesPool& rSrcPool )
{
    TraceClientCore::CRepositoryObserver::Accessor              ROAccess(m_RepositoryObserver);
	TraceClientCore::CTraceDataRepositoryLinkBase*				pLink = ROAccess->Links().GetLinkContains(rSrcPool);

	if ( NULL != pLink )
		ROAccess->Links().Remove(pLink);
}


/**
 *
 */
bool CTracesRepositoryDoc::Contains( const TraceClientCore::CTracesPool& rSrcPool )
{
    TraceClientCore::CRepositoryObserver::Accessor              ROAccess(m_RepositoryObserver);

	return ROAccess->Links().Contains(rSrcPool);
}


/**
 *
 */
void CTracesRepositoryDoc::OnNewTraceItems()
{
    emit sig_OnNewTraceItems();
}

