#include <Nyx.hpp>

#include "TracesGroupMgrListener.h"


CTracesGroupMgrListener::CTracesGroupMgrListener() : QObject(),
    m_pListener(NULL)
{
    m_pListener = new XListener(this);

    TraceClientCore::CModule& rModule = TraceClientCore::CModule::Instance();

    rModule.TracesGroupMgr().Listeners().Add(m_pListener);
}


CTracesGroupMgrListener::~CTracesGroupMgrListener()
{

}


void CTracesGroupMgrListener::OnNewTracesGroup(TraceClientCore::CTracesGroup *pGroup)
{
    emit NewTracesGroup(pGroup);
}


void CTracesGroupMgrListener::OnTracesGroupWillBeDeleted(TraceClientCore::CTracesGroup *pGroup)
{

}
