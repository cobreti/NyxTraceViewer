#include "TracesViewCoreRepositoryObserver.hpp"
#include "View/ViewItem_TraceData.hpp"

/**
 *
 */
CTracesViewCoreRepositoryObserver::CTracesViewCoreRepositoryObserver(CTracesViewCore& rViewCore) :
    TraceClientCore::CRepositoryObserver(),
    m_rViewCore(rViewCore),
    m_pItems(NULL)
{
}


/**
 *
 */
CTracesViewCoreRepositoryObserver::~CTracesViewCoreRepositoryObserver()
{
}


/**
 *
 */
void CTracesViewCoreRepositoryObserver::Insert( TraceClientCore::CTraceData* pTraceData )
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
void CTracesViewCoreRepositoryObserver::OnFirstBeginUpdate()
{
    if ( m_pItems == NULL )
        m_pItems = new (m_refObjectsPool)CViewItems(m_refObjectsPool, false);
}


/**
 *
 */
void CTracesViewCoreRepositoryObserver::OnFinalEndUpdate()
{
    if ( m_pItems->ItemsCount() > 0 )
    {
//        m_rDocument.OnNewTraceItems(m_pItems);
        m_pItems = NULL;
    }
}

