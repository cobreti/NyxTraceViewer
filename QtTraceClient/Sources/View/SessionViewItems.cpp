#include "SessionViewItems.hpp"
#include "ViewItemsModulesMgr.hpp"

/**
 *
 */
CSessionViewItems::CSessionViewItems(CViewItemsModulesMgr& rMgr) :
    m_Items(rMgr.MemoryPool(), false),
    m_rMgr(rMgr)
{
}


/**
 *
 */
CSessionViewItems::~CSessionViewItems()
{
}


