#include "TracesViewCore.hpp"
#include "TracesView.h"
#include "ViewItem.hpp"
#include "ViewItemsModulesMgr.hpp"
#include "ViewItemPos.hpp"
#include "ViewItems.hpp"
#include "TracesViewCoreRepositoryObserver.hpp"
#include "TraceClientApp.h"


/**
 *
 */
CTracesViewCore::CTracesViewCore() :
    Nyx::CRefCount_Impl<Nyx::CMsgHandler>(),
    m_pViewItemsModulesMgr(NULL),
    m_pRepositoryObserver(NULL),
    m_NextLineId(1)
{
    Init();
}


/**
 *
 */
CTracesViewCore::~CTracesViewCore()
{
    delete m_pViewItemsModulesMgr;
}


/**
 *
 */
Nyx::CMsgHandler* CTracesViewCore::GetViewItemsMsgHandler()
{
    return static_cast<Nyx::CMsgHandler*>(this);
}


/**
 *
 */
void CTracesViewCore::AddView(CTracesView *pView)
{
    m_Views.Insert(pView);
}


/**
 *
 */
void CTracesViewCore::RemoveView(CTracesView* pView)
{
    m_Views.Remove(pView);
}


/**
 *
 */
CTracesViewSetIterator CTracesViewCore::GetViewsIterator() const
{
    CTracesViewSetIterator      iter(m_Views);
    iter.MoveToFirst();

    return iter;
}


/**
 *
 */
void CTracesViewCore::AddRepository(TraceClientCore::CTracesPool &rPool)
{
    rPool.Repository().Insert(m_pRepositoryObserver);
}


/**
 *
 */
void CTracesViewCore::RemoveRepository(TraceClientCore::CTracesPool &rPool)
{
    rPool.Repository().Remove(m_pRepositoryObserver);
}


/**
 *
 */
bool CTracesViewCore::Contains(const TraceClientCore::CTracesPool &rPool)
{
    return rPool.Repository().Contains(m_pRepositoryObserver);
}


/**
 *
 */
void CTracesViewCore::HandleMessage( Nyx::CMsg& msg )
{
    switch ( msg.Id() )
    {
        case 0:
            OnNewTraces( static_cast<CViewItemsMsg&>(msg).ViewItems() );
            break;
        case 1:
            OnClearTraces( static_cast<CClearItemsMsg&>(msg).ModuleName() );
            break;
    };

}


/**
 *
 */
void CTracesViewCore::Init()
{
    m_refMemoryPool = Nyx::CMemoryPool::Alloc(100);

    m_pViewItemsModulesMgr = new CViewItemsModulesMgr(m_refMemoryPool);
    m_pRepositoryObserver = new CTracesViewCoreRepositoryObserver(*this);

    m_ViewSettings = CTraceClientApp::Instance().AppSettings().DefaultViewSettings();

    m_ViewSettings.DrawSettings() = &CTraceClientApp::Instance().AppSettings().DefaultDrawSettings();
}


/**
 *
 */
void CTracesViewCore::OnNewTraces(CViewItems *pViewItems)
{
    CViewItemPos        posItem = pViewItems->begin();
    while ( posItem.IsValid() )
    {
        posItem.Item()->Id() = m_NextLineId ++;
        m_pViewItemsModulesMgr->Insert( posItem.Item() );
        ++posItem;
    }

    CTracesViewSetIterator      ViewIter(m_Views);

    ViewIter.MoveToFirst();

    while ( ViewIter.Valid() )
    {
        ViewIter.View()->OnNewTraces();
        ViewIter.MoveToNext();
    }

    delete pViewItems;
}


/**
 *
 */
void CTracesViewCore::OnClearTraces(const Nyx::CAString& ModuleName)
{
    Nyx::CWString   wModuleName;

    wModuleName = ModuleName;

    m_pViewItemsModulesMgr->ClearModule(wModuleName);

    CTracesViewSetIterator      ViewPos(m_Views);

    ViewPos.MoveToFirst();

    while ( ViewPos.Valid() )
    {
        ViewPos.View()->OnModuleRemoved(ModuleName);
        ViewPos.MoveToNext();
    }
}

