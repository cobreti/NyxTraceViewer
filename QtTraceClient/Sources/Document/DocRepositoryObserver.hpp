#ifndef _DOCREPOSITORYOBSERVER_HPP_
#define _DOCREPOSITORYOBSERVER_HPP_

#include "RepositoryObserver.hpp"
#include "View/ViewItems.hpp"

class CTracesDocument;

/**
 *
 */
class CDocRepositoryObserver : public TraceClientCore::CRepositoryObserver
{
public:
    CDocRepositoryObserver( CTracesDocument& rDocument );
    virtual ~CDocRepositoryObserver();

    virtual void Insert( TraceClientCore::CTraceData* pTraceData );

protected:

        virtual void OnFirstBeginUpdate();
        virtual void OnFinalEndUpdate();

protected:

    CViewItems*             m_pItems;
    CTracesDocument&        m_rDocument;
};


#endif // _DOCREPOSITORYOBSERVER_HPP_
