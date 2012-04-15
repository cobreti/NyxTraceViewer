#ifndef TRACESVIEWCORE_HPP
#define TRACESVIEWCORE_HPP

#include <Nyx.hpp>

class CViewItemsModulesMgr;
class CTracesViewCoreRepositoryObserver;

DECLARE_OBJECTREF(CTracesViewCore)

/**
 *
 */
class CTracesViewCore : public Nyx::CRefCount_Impl<>
{
public:
    CTracesViewCore();
    virtual ~CTracesViewCore();

protected:
    Nyx::CMemoryPoolRef                                     m_refMemoryPool;
    CViewItemsModulesMgr*                                   m_pViewItemsModulesMgr;
    CTracesViewCoreRepositoryObserver*                      m_pRepositoryObserver;
};



#endif // TRACESVIEWCORE_HPP
