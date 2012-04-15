#include "DocRepositoryObserver.hpp"
#include "View/ViewItem_TraceData.hpp"
//#include "View/ViewItemBackgroundPainter.hpp"
//#include "View/ViewItemModuleNamePainter.hpp"
//#include "View/ViewItemTickCountPainter.hpp"
//#include "View/ViewItemThreadIdPainter.hpp"
//#include "View/ViewItemDataPainter.hpp"
//#include "View/ViewItemLineNumberPainter.hpp"
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
    Nyx::CRangesArray           SplitRanges;

    pTraceData->Data().GetSplitRanges('\n', SplitRanges);

    if ( SplitRanges.size() > 0 )
    {
        CViewItem_TraceData*        pParentItem = new (pMemPool)CViewItem_TraceData(pMemPool, pTraceData);
        pParentItem->TextRange() = SplitRanges[0];
        pParentItem->SetFlag( CViewItem::eVIF_ApproxSize );
        pParentItem->SetOwner(pParentItem);
        m_pItems->Add(pParentItem);

        size_t index = 1;
        while (index < SplitRanges.size())
        {
            CViewItem_TraceData*        pItem = new (pMemPool)CViewItem_TraceData(pMemPool, pTraceData);
            pItem->TextRange() = SplitRanges[index];
            pItem->SetFlag( CViewItem::eVIF_ApproxSize );
            pItem->SetOwner( pParentItem );
            m_pItems->Add(pItem);

            ++index;
        }

    }
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
