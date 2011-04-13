#ifndef DOCOBSERVERNOTIFICATIONSHANDLER_HPP
#define DOCOBSERVERNOTIFICATIONSHANDLER_HPP

#include <RepositoryObserverNotificationsHandler.hpp>
#include <TraceInserter.hpp>

class CTracesDocument;
class CViewItemsQueue;

class CDocObserverNotificationsHandler :    public TraceClientCore::CRepositoryObserverNotificationsHandler,
                                            public TraceClientCore::CTraceInserter
{
public:
    CDocObserverNotificationsHandler(CTracesDocument& rDoc);
    virtual ~CDocObserverNotificationsHandler();

    virtual void OnNewItems();
    virtual TraceClientCore::CTraceInserter* OnBeginCheckUpdate();
    virtual void OnEndCheckUpdate();

    virtual void Insert( TraceClientCore::CTraceData* pTraceData );

protected:

    CTracesDocument&        m_rDoc;

    CViewItemsQueue*        m_pItemsQueue;
};

#endif // DOCOBSERVERNOTIFICATIONSHANDLER_HPP
