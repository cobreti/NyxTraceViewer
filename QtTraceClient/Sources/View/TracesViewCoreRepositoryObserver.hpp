#ifndef TRACESVIEWCOREREPOSITORYOBSERVER_HPP
#define TRACESVIEWCOREREPOSITORYOBSERVER_HPP

#include "RepositoryObserver.hpp"
#include "ViewItems.hpp"
#include <NyxObjectsPool.hpp>

class CTracesViewCore;

/**
 *
 */
class CTracesViewCoreRepositoryObserver : TraceClientCore::CRepositoryObserver
{
public:
    CTracesViewCoreRepositoryObserver(CTracesViewCore& rViewCore);
    virtual ~CTracesViewCoreRepositoryObserver();

    virtual void Insert( TraceClientCore::CTraceData* pTraceData );

protected:

    virtual void OnFirstBeginUpdate();
    virtual void OnFinalEndUpdate();

protected:
    CViewItems*                     m_pItems;
//    CTracesDocument&                m_rDocument;
    CTracesViewCore&                m_rViewCore;
    Nyx::CObjectsPoolRef            m_refObjectsPool;
};

#endif // TRACESVIEWCOREREPOSITORYOBSERVER_HPP
