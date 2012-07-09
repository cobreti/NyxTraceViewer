#ifndef _VIEWITEMSWALKERNODESPOOL_HPP_
#define _VIEWITEMSWALKERNODESPOOL_HPP_

#include <Nyx.hpp>

/**
 *
 */
class CViewItemsWalkerNodesPool : public Nyx::CObjectsPool
{
public:
    static CViewItemsWalkerNodesPool*       Instance();

    CViewItemsWalkerNodesPool();
    ~CViewItemsWalkerNodesPool();

    virtual void Retain() const {}
    virtual void Release() const {}

    virtual void* AllocMem(size_t size)         { return m_refObjectsPool->AllocMem(size); }
    virtual void FreeMem(void* pBlock)          { m_refObjectsPool->FreeMem(pBlock); }
    virtual void Clear()                        { m_refObjectsPool->Clear(); }

protected:

    Nyx::CObjectsPoolRef                    m_refObjectsPool;

    static CViewItemsWalkerNodesPool*       s_pInstance;
};

#endif // VIEWITEMSWALKERNODESPOOL_HPP
