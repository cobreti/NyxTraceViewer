#include "ViewItemsWalkerNodesPool.hpp"


/**
 *
 */
CViewItemsWalkerNodesPool*       CViewItemsWalkerNodesPool::s_pInstance = NULL;


/**
 *
 */
CViewItemsWalkerNodesPool* CViewItemsWalkerNodesPool::Instance()
{
    return s_pInstance;
}

/**
 *
 */
CViewItemsWalkerNodesPool::CViewItemsWalkerNodesPool()
{
    m_refObjectsPool = Nyx::CObjectsPool::Alloc(2048);
    s_pInstance = this;
}


/**
 *
 */
CViewItemsWalkerNodesPool::~CViewItemsWalkerNodesPool()
{
    s_pInstance = NULL;
}
