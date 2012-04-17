#include "ViewItemsWalker.hpp"


/**
 *
 */
CViewItemsWalker::CViewItemsWalker(CViewItemsModulesMgr& rViewItemsModulesMgr) :
    CViewItemsWalkerCore(rViewItemsModulesMgr)
{
    m_refMutex = Nyx::CMutex::Alloc();
}


/**
 *
 */
CViewItemsWalker::CViewItemsWalker(const CViewItemsWalker &walker) :
    CViewItemsWalkerCore(walker)
{
    m_refMutex = Nyx::CMutex::Alloc();
}


/**
 *
 */
CViewItemsWalker::~CViewItemsWalker()
{
}


/**
 *
 */
void CViewItemsWalker::Clone(const CViewItemsWalker &walker)
{
    Nyx::TLock<Nyx::CMutex>     lock(m_refMutex, true);
    Nyx::TLock<Nyx::CMutex>     srcLock(walker.m_refMutex, true);

    CViewItemsWalkerCore::Clone(walker);
}


/**
 *
 */
void CViewItemsWalker::Lock(IViewItemsWalkerMethods*& pWalkerMethods)
{
    m_refMutex->Lock();

    pWalkerMethods = static_cast<IViewItemsWalkerMethods*>(this);
}


/**
 *
 */
void CViewItemsWalker::Unlock( IViewItemsWalkerMethods*& pWalkerMethods )
{
    pWalkerMethods = NULL;
    m_refMutex->Unlock();
}


