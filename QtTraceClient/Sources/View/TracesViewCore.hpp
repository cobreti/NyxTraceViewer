#ifndef TRACESVIEWCORE_HPP
#define TRACESVIEWCORE_HPP

#include <Nyx.hpp>
#include <NyxMsgHandler.hpp>
#include "TracesViewSet.hpp"
#include "TracesPool.hpp"

class CViewItemsModulesMgr;
class CTracesViewCoreRepositoryObserver;
class CViewItems;

DECLARE_OBJECTREF(CTracesViewCore)

/**
 *
 */
class CTracesViewCore : public Nyx::CRefCount_Impl<Nyx::CMsgHandler>
{
    friend class CTracesDocument;

public:
    CTracesViewCore();
    virtual ~CTracesViewCore();

    CViewItemsModulesMgr&           ViewItemsModulesMgr()           { return *m_pViewItemsModulesMgr; }
    const CViewItemsModulesMgr&     ViewItemsModulesMgr() const     { return *m_pViewItemsModulesMgr; }

    Nyx::CMemoryPool*               MemoryPool() const              { return m_refMemoryPool; }

    Nyx::CMsgHandler* GetViewItemsMsgHandler();

    void AddView( CTracesView* pView );

    CTracesViewSetIterator GetViewsIterator() const;

    void AddRepository( TraceClientCore::CTracesPool& rPool );
    void RemoveRepository( TraceClientCore::CTracesPool& rPool );
    bool Contains( const TraceClientCore::CTracesPool& rPool );

public: // CMsgHandler

    virtual Nyx::MsgIdentifier Id() const { return 0; }
    virtual void HandleMessage( Nyx::CMsg& msg );

protected:

    void Init();

    void OnNewTraces( CViewItems* pViewItems );

protected:
    Nyx::CMemoryPoolRef                                     m_refMemoryPool;
    CViewItemsModulesMgr*                                   m_pViewItemsModulesMgr;
    CTracesViewCoreRepositoryObserver*                      m_pRepositoryObserver;
    size_t                                                  m_NextLineId;
    CTracesViewSet                                          m_Views;
};



#endif // TRACESVIEWCORE_HPP
