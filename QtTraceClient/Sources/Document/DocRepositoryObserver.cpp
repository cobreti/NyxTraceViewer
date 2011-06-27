#include "DocRepositoryObserver.hpp"
#include "View/ViewItem_TraceData.hpp"
#include "View/ViewItemBackgroundPainter.hpp"
#include "View/ViewItemModuleNamePainter.hpp"
#include "View/ViewItemTickCountPainter.hpp"
#include "View/ViewItemThreadIdPainter.hpp"
#include "View/ViewItemDataPainter.hpp"
#include "View/ViewItemLineNumberPainter.hpp"
#include "TracesDocument.hpp"

/**
 *
 */
CDocRepositoryObserver::CDocRepositoryObserver(CTracesDocument& rDocument) : TraceClientCore::CRepositoryObserver(),
m_rDocument(rDocument),
m_pItems(NULL)
{
    m_refObjectsPool = Nyx::CObjectsPool::Alloc( sizeof(CViewItems)*5 );
}


/**
 *
 */
CDocRepositoryObserver::~CDocRepositoryObserver()
{
}


/**
 *
 */
void CDocRepositoryObserver::Insert( TraceClientCore::CTraceData* pTraceData )
{
    Nyx::CMemoryPool*           pMemPool = pTraceData->MemoryPool();
    CViewItem_TraceData*        pItem = new (pMemPool)CViewItem_TraceData(pMemPool, pTraceData);

    pItem->Painters().Add( CViewItemBackgroundPainter::Instance() );
    pItem->Painters().Add( CViewItemLineNumberPainter::Instance() );
    pItem->Painters().Add( CViewItemModuleNamePainter::Instance() );
    pItem->Painters().Add( CViewItemTickCountPainter::Instance() );
    pItem->Painters().Add( CViewItemThreadIdPainter::Instance() );
    pItem->Painters().Add( CViewItemDataPainter::Instance() );
    pItem->SetFlag( CViewItem::eVIF_ApproxSize );

    m_pItems->Add(pItem);
}


/**
 *
 */
void CDocRepositoryObserver::OnFirstBeginUpdate()
{
    if ( m_pItems == NULL )
        m_pItems = new (m_refObjectsPool)CViewItems(m_refObjectsPool, false);
}


/**
 *
 */
void CDocRepositoryObserver::OnFinalEndUpdate()
{
    if ( m_pItems->ItemsCount() > 0 )
    {
        m_rDocument.OnNewTraceItems(m_pItems);
        m_pItems = NULL;
    }
}
