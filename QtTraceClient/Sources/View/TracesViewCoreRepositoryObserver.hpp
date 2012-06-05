#ifndef _TRACESVIEWCOREREPOSITORYOBSERVER_HPP_
#define _TRACESVIEWCOREREPOSITORYOBSERVER_HPP_

#include "RepositoryObserver.hpp"
#include "View/ViewItems.hpp"
#include "NyxObjectsPool.hpp"
#include "NyxActiveObject.hpp"


class CTracesViewCore;


/**
 *
 */
class CTracesViewCoreRepositoryObserver : public TraceClientCore::CRepositoryObserver
{
public:
    CTracesViewCoreRepositoryObserver( CTracesViewCore& rViewCore );
    virtual ~CTracesViewCoreRepositoryObserver();

    virtual void Insert( TraceClientCore::CTraceData* pTraceData );
    virtual void Clear(const Nyx::CAString& ModuleName);

protected:

        virtual void OnFirstBeginUpdate();
        virtual void OnFinalEndUpdate();

protected:
    CTracesViewCore&                m_rViewCore;
    CViewItems*                     m_pItems;
    Nyx::CObjectsPoolRef            m_refObjectsPool;
    Nyx::CActiveObjectRef           m_refActiveObject;
};

#endif // _TRACESVIEWCOREREPOSITORYOBSERVER_HPP_
