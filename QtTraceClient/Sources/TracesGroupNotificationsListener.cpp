#include "TracesGroupNotificationsListener.h"


CTracesGroupNotificationsListener::CTracesGroupNotificationsListener() : QObject(),
    m_Listener(this),
    m_pTracesGroup(NULL)
{

}


CTracesGroupNotificationsListener::~CTracesGroupNotificationsListener()
{

}


void CTracesGroupNotificationsListener::ConnectTo( TraceClientCore::CTracesGroup* pGroup )
{
    if ( pGroup == m_pTracesGroup )
        return;

    Disconnect();

    m_pTracesGroup = pGroup;

    if ( NULL != m_pTracesGroup )
    {
        m_pTracesGroup->Listeners().Add(&m_Listener);
    }
}


void CTracesGroupNotificationsListener::Disconnect()
{
    if ( NULL != m_pTracesGroup )
    {
        m_pTracesGroup->Listeners().Remove(&m_Listener);
        m_pTracesGroup = NULL;
    }
}


void CTracesGroupNotificationsListener::OnViewBeginUpdate( TraceClientCore::CTracesGroup* pGroup, TraceClientCore::CTracesView* pView )
{
    emit ViewBeginUpdate(pGroup, pView);
}


void CTracesGroupNotificationsListener::OnViewEndUpdate( TraceClientCore::CTracesGroup* pGroup, TraceClientCore::CTracesView* pView )
{
    emit ViewEndUpdate(pGroup, pView);
}

