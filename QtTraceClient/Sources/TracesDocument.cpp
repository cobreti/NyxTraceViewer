#include "TracesDocument.hpp"
#include "TracesView.h"

//#include "TraceDataRepositoryToDocumentLink.hpp"
#include "DocObserverNotificationsHandler.hpp"
#include "TracesPool.hpp"
#include "View/ViewColumnSettings.hpp"

/**
 *
 */
CTracesDocument::CTracesDocument(QWidget* pDefaultViewsParentWindow, const QString& name) :
m_pDefaultViewsParentWindow(pDefaultViewsParentWindow),
m_Name(name),
m_RefreshTimer(this),
m_RepositoryObserver(*this)
{
    connect(this, SIGNAL(sig_OnNewTraceItems(CViewItems*)), this, SLOT(OnNewTraceItemsHandler(CViewItems*)));
    connect( &m_RefreshTimer, SIGNAL(timeout()), this, SLOT(OnRefreshTimer()));

    m_RefreshTimer.start(1000);
}


/**
 *
 */
CTracesDocument::~CTracesDocument()
{
    Nyx::CTraceStream(0x0).Write(L"CTracesDocument::~CTracesDocument");
}


/**
 *
 */
void CTracesDocument::Init()
{
    CViewItemSettings*      pSetting = NULL;
    QFont*                  pFont = new QFont("Courier New", 10);
    QFontMetricsF           TextMetrics(*pFont);

    CViewColumnSettings*		pColSettings = NULL;

    // Module name
    pColSettings = new CViewColumnSettings();
    pColSettings->SetWidth(0);
    pColSettings->Margins() = CViewItemMargins(10, 0, 10, 0);
    pColSettings->AutoWidth() = true;
    pColSettings->SetPainterId( CViewItemPainter::ePId_ModuleName );
    pColSettings->SetTitle("Module Name");
    pColSettings->SetWidth( TextMetrics.boundingRect(pColSettings->GetTitle()).width() + pColSettings->Margins().width());
    DefaultViewSettings().ColumnsSettings().Set( eVCI_ModuleName, pColSettings );

    // TickCount
    pColSettings = new CViewColumnSettings();
    pColSettings->SetWidth(0);
    pColSettings->Margins() = CViewItemMargins(10, 0, 10, 0);
    pColSettings->AutoWidth() = true;
    pColSettings->SetPainterId( CViewItemPainter::ePId_TickCount );
    pColSettings->SetTitle("TickCount");
    pColSettings->SetWidth( TextMetrics.boundingRect(pColSettings->GetTitle()).width() + pColSettings->Margins().width());
    DefaultViewSettings().ColumnsSettings().Set( eVCI_TickCount, pColSettings );

    // ThreadId
    pColSettings = new CViewColumnSettings();
    pColSettings->SetWidth(0);
    pColSettings->Margins() = CViewItemMargins(10, 0, 10, 0);
    pColSettings->AutoWidth() = true;
    pColSettings->SetPainterId( CViewItemPainter::ePId_ThreadId );
    pColSettings->SetTitle("Thread Id");
    pColSettings->SetWidth( TextMetrics.boundingRect(pColSettings->GetTitle()).width() + pColSettings->Margins().width());
    DefaultViewSettings().ColumnsSettings().Set( eVCI_ThreadId, pColSettings );

    // data
    pColSettings = new CViewColumnSettings();
    pColSettings->SetWidth(0);
    pColSettings->Margins() = CViewItemMargins(10, 0, 20, 0);
    pColSettings->AutoWidth() = true;
    pColSettings->SetPainterId( CViewItemPainter::ePId_Data );
    pColSettings->SetTitle("Data");
    pColSettings->SetWidth( TextMetrics.boundingRect(pColSettings->GetTitle()).width() + pColSettings->Margins().width());
    DefaultViewSettings().ColumnsSettings().Set( eVCI_Data, pColSettings );

    DefaultViewSettings().ViewItemsSettings().GetDefault()->SetFont(pFont);

    pSetting = new CViewItemSettings();
    pSetting->SetFont( new QFont("Courier New", 10 ) );
//    pSetting->SetMargins( CViewItemMargins(5, 0, 5, 0) );
    DefaultViewSettings().ViewItemsSettings().Add( CViewItemPainter::ePId_TickCount, pSetting );

    pSetting = new CViewItemSettings();
    pSetting->SetFont( new QFont("Courier New", 10 ) );
//    pSetting->SetMargins( CViewItemMargins(5, 0, 5, 0) );
    DefaultViewSettings().ViewItemsSettings().Add( CViewItemPainter::ePId_ThreadId, pSetting );

    pSetting = new CViewItemSettings();
    pSetting->SetFont( new QFont("Courier New", 9, 2) );
    DefaultViewSettings().ViewItemsSettings().Add( CViewItemPainter::ePId_Header, pSetting );

 //   TraceClientCore::CRepositoryObserver::Accessor       ROAccess(m_RepositoryObserver);

	//ROAccess->NotificationsHandler() = new CDocObserverNotificationsHandler(*this);
 //   ROAccess->Start();
}


/**
 *
 */
void CTracesDocument::Destroy()
{
    m_RefreshTimer.stop();

	//{
	//	TraceClientCore::CRepositoryObserver::Accessor		ROAccess(m_RepositoryObserver);

	//	ROAccess->Stop();
	//	ROAccess->NotificationsHandler() = NULL;

	//	while ( !m_UsedLinks.empty() )
	//	{
	//		TraceClientCore::CTraceDataRepositoryLinkBaseRef	refLink = m_UsedLinks.front();
	//		ROAccess->Links().Remove( refLink );
	//		m_UsedLinks.pop_front();
	//	}

	//}

	Nyx::CTraceStream(0x0).Write(L"before clearing the repository");

	while ( !m_Views.empty() )
	{
		m_Views.front()->close();
		delete m_Views.front();
		m_Views.pop_front();
	}

    m_ViewItems.Clear(false);
}


/**
 *
 */
CTracesView* CTracesDocument::CreateView(QWidget* pParent)
{
    CTracesView*        pView = new CTracesView(*this, pParent);

    pView->Settings().ViewItemsSettings() = DefaultViewSettings().ViewItemsSettings();
    m_Views.push_back(pView);
    pView->setParent(NULL/*m_pDefaultViewsParentWindow*/, Qt::Window);
    //pView->show();

    return pView;
}


/**
 *
 */
void CTracesDocument::GetViews( CTracesDocument::TracesViewList& ViewsList ) const
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
void CTracesDocument::AddRepositorySrc( TraceClientCore::CTracesPool& rSrcPool )
{
    rSrcPool.Repository().Insert( &m_RepositoryObserver );
 //   TraceClientCore::CRepositoryObserver::Accessor              ROAccess(m_RepositoryObserver);
 //   CTraceDataRepositoryToDocumentLink*                         pLink = new CTraceDataRepositoryToDocumentLink(rSrcPool);

 //   ROAccess->Links().Add(pLink);

	//m_UsedLinks.push_back(pLink);
}


/**
 *
 */
void CTracesDocument::RemoveRepositorySrc( TraceClientCore::CTracesPool& rSrcPool )
{
    rSrcPool.Repository().Remove( &m_RepositoryObserver );
 //   TraceClientCore::CRepositoryObserver::Accessor              ROAccess(m_RepositoryObserver);
	//TraceClientCore::CTraceDataRepositoryLinkBase*				pLink = ROAccess->Links().GetLinkContains(rSrcPool);

	//if ( NULL != pLink )
	//	ROAccess->Links().Remove(pLink);
}


/**
 *
 */
bool CTracesDocument::Contains( const TraceClientCore::CTracesPool& rSrcPool )
{
 //   TraceClientCore::CRepositoryObserver::Accessor              ROAccess(m_RepositoryObserver);

	//return ROAccess->Links().Contains(rSrcPool);

    return rSrcPool.Repository().Contains(&m_RepositoryObserver);
}


/**
 *
 */
void CTracesDocument::OnNewTraceItems(CViewItems* pViewItems)
{
    emit sig_OnNewTraceItems(pViewItems);
}


/**
 *
 */
void CTracesDocument::OnNewTraceItemsHandler(CViewItems* pViewItems)
{
    m_ViewItems += *pViewItems;

    TracesViewList::iterator        pos = m_Views.begin();

    while ( pos != m_Views.end() )
    {
        (*pos)->OnNewTraces();
        ++pos;
    }

    pViewItems->Clear(false);
    delete pViewItems;
}


/**
 *
 */
void CTracesDocument::OnRefreshTimer()
{
    TracesViewList::iterator        pos = m_Views.begin();

    for (pos = m_Views.begin(); pos != m_Views.end(); ++pos)
        (*pos)->UpdateVisibleLines(DefaultViewSettings());

    for (pos = m_Views.begin(); pos != m_Views.end(); ++pos)
        (*pos)->RefreshDisplay();
}

