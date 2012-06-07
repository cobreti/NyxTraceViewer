#include "SessionViewItems.hpp"
#include "ViewItemsModulesMgr.hpp"
#include "View/ViewItem.hpp"

/**
 *
 */
CSessionViewItems::CSessionViewItems(CViewItemsModulesMgr& rMgr) :
    m_Items(rMgr.MemoryPool(), false),
    m_rMgr(rMgr),
    m_Height(0.0)
{
}


/**
 *
 */
CSessionViewItems::~CSessionViewItems()
{
}


/**
 *
 */
void CSessionViewItems::Add(CViewItem *pItem)
{
    m_Items.Add(pItem);
    m_Height += pItem->GetSize().height();
}
