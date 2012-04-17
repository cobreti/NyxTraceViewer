#ifndef VIEWITEMSWALKER_HPP
#define VIEWITEMSWALKER_HPP

#include <Nyx.hpp>

#include "ViewItemsWalkerCore.hpp"

/**
 *
 */
class CViewItemsWalker : protected CViewItemsWalkerCore
{
public:

    typedef     Nyx::CInterfaceRef<IViewItemsWalkerMethods, CViewItemsWalker>       MethodsInterfaceRef;

public:
    CViewItemsWalker(CViewItemsModulesMgr& rViewItemsModulesMgr);
    explicit CViewItemsWalker(const CViewItemsWalker& walker);
    virtual ~CViewItemsWalker();

    virtual void Clone( const CViewItemsWalker& walker );

    void Lock( IViewItemsWalkerMethods*& pWalkerMethods );
    void Unlock( IViewItemsWalkerMethods*& pWalkerMethods );

protected:

    Nyx::CMutexRef      m_refMutex;

};

#endif // VIEWITEMSWALKER_HPP
