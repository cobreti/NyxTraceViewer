#include <Nyx.hpp>
#include "DocObserverNotificationsHandler.hpp"
#include "TracesDocument.hpp"
#include "View/ViewItems.hpp"
#include "View/ViewItemsQueue.hpp"


/**
 *
 */
CDocObserverNotificationsHandler::CDocObserverNotificationsHandler(CTracesDocument& rDoc) :
TraceClientCore::CRepositoryObserverNotificationsHandler(),
m_rDoc(rDoc),
m_pItemsQueue(NULL)
{
    m_pItemsQueue = new CViewItemsQueue();
    m_pItemsQueue->SetViewItems( new CViewItems() );
}


/**
 *
 */
CDocObserverNotificationsHandler::~CDocObserverNotificationsHandler()
{
    CViewItems* pItems = m_pItemsQueue->Detach();
    delete pItems;
    delete m_pItemsQueue;
}


/**
 *
 */
void CDocObserverNotificationsHandler::OnNewItems()
{
}


/**
 *
 */
TraceClientCore::CTraceInserter* CDocObserverNotificationsHandler::OnBeginCheckUpdate()
{
    return static_cast<TraceClientCore::CTraceInserter*>(this);
}


/**
 *
 */
void CDocObserverNotificationsHandler::OnEndCheckUpdate()
{
    CViewItems* pItems = m_pItemsQueue->Top();

    if ( pItems->ItemsCount() > 0 )
        m_rDoc.OnNewTraceItems(pItems);
}


/**
 *
 */
void CDocObserverNotificationsHandler::Insert( TraceClientCore::CTraceData* pTraceData )
{
    m_pItemsQueue->InsertViewItem(pTraceData);
}
