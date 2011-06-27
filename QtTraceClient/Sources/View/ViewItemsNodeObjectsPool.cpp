#include "ViewItemsNodeObjectsPool.hpp"

/**
 *
 */
CViewItemsNodeObjectsPool* CViewItemsNodeObjectsPool::s_pInstance = NULL;


/**
 *
 */
CViewItemsNodeObjectsPool* CViewItemsNodeObjectsPool::Instance()
{
    return s_pInstance;
}


/**
 *
 */
CViewItemsNodeObjectsPool::CViewItemsNodeObjectsPool()
{
    m_refObjectsPool = Nyx::CObjectsPool::Alloc(2048);
    s_pInstance = this;
}


/**
 *
 */
CViewItemsNodeObjectsPool::~CViewItemsNodeObjectsPool()
{
    s_pInstance = NULL;
}

