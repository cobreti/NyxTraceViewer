#include "TracesViewCore.hpp"
#include "TracesView.h"
#include "ViewItem.hpp"
#include "ViewItemsModulesMgr.hpp"
#include "ViewItemPos.hpp"
#include "ViewItems.hpp"
#include "TracesViewCoreRepositoryObserver.hpp"


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
    OnNewTraces( static_cast<CViewItemsMsg&>(msg).ViewItems() );
}


/**
 *
 */
void CTracesViewCore::Init()
{
    m_refMemoryPool = Nyx::CMemoryPool::Alloc(100);

    m_pViewItemsModulesMgr = new CViewItemsModulesMgr(m_refMemoryPool);
    m_pRepositoryObserver = new CTracesViewCoreRepositoryObserver(*this);
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

//    TracesViewList::iterator        pos = m_Views.begin();

//    while ( pos != m_Views.end() )
//    {
//        (*pos)->OnNewTraces();
//        ++pos;
//    }

    delete pViewItems;
}
