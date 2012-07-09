#ifndef _VIEWITEMSNODEOBJECTSPOOL_HPP_
#define _VIEWITEMSNODEOBJECTSPOOL_HPP_

#include <Nyx.hpp>
#include <NyxObjectsPool.hpp>


/**
 *
 */
class CViewItemsNodeObjectsPool : public Nyx::CObjectsPool
{
public:
    static CViewItemsNodeObjectsPool* Instance();

    CViewItemsNodeObjectsPool();
    virtual ~CViewItemsNodeObjectsPool();

    virtual void Retain() const {}
    virtual void Release() const {}

    virtual void* AllocMem(size_t size)         { return m_refObjectsPool->AllocMem(size); }
    virtual void FreeMem(void* pBlock)          { m_refObjectsPool->FreeMem(pBlock); }
    virtual void Clear()                        { m_refObjectsPool->Clear(); }


protected:

    Nyx::CObjectsPoolRef                    m_refObjectsPool;

    static CViewItemsNodeObjectsPool*       s_pInstance;
};


#endif // _VIEWITEMSNODEOBJECTSPOOL_HPP_
