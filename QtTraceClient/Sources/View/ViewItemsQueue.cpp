#include "ViewItemsQueue.hpp"
#include "View/ViewItem_TraceData.hpp"
#include "View/ViewItems.hpp"
#include "View/ViewItemBackgroundPainter.hpp"
#include "View/ViewItemModuleNamePainter.hpp"
#include "View/ViewItemTickCountPainter.hpp"
#include "View/ViewItemThreadIdPainter.hpp"
#include "View/ViewItemDataPainter.hpp"

#include <Nyx.hpp>

/**
 *
 */
CViewItemsQueue::CViewItemsQueue() : CViewItemInserter()
{
}


/**
 *
 */
void CViewItemsQueue::SetViewItems( CViewItems* pViewItems )
{
    m_pTop = pViewItems;
}


/**
 *
 */
CViewItems* CViewItemsQueue::Detach()
{
    CViewItems* pRet = m_pTop;
    m_pTop = NULL;
    return pRet;
}


/**
 *
 */
void CViewItemsQueue::InsertViewItem( const TraceClientCore::CTraceData* pTraceData )
{
    if ( !m_pTop )
        return;

    Nyx::CMemoryPool*           pMemPool = pTraceData->MemoryPool();
    CViewItem_TraceData*        pItem = new (pMemPool)CViewItem_TraceData(pMemPool, pTraceData);

    pItem->Painters().Add( CViewItemBackgroundPainter::Instance() );
    pItem->Painters().Add( CViewItemModuleNamePainter::Instance() );
    pItem->Painters().Add( CViewItemTickCountPainter::Instance() );
    pItem->Painters().Add( CViewItemThreadIdPainter::Instance() );
    pItem->Painters().Add( CViewItemDataPainter::Instance() );
    pItem->SetFlag( CViewItem::eVIF_ApproxSize );
//    pItem->SetSize( m_MaxLineSize );
    //pItem->EvaluateSize(Settings());
    //m_Items.Add(pItem);

    m_pTop->Add(pItem);
}

