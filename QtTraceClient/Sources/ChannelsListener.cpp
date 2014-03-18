#include <Nyx.hpp>

#include "ChannelsListener.h"


CChannelsListener::CChannelsListener() : QObject(),
    m_pListener(NULL)
{
    m_pListener = new XListener(this);

    TraceClientCore::CModule& rModule = TraceClientCore::CModule::Instance();

    rModule.ChannelsMgr().AddListener(m_pListener);
}


CChannelsListener::~CChannelsListener()
{

}


void CChannelsListener::OnNewChannel(TraceClientCore::CTraceChannel *pChannel)
{
    emit newChannel(pChannel);

    TraceClientCore::CTracesGroup*      pTracesGroup = NULL;

    pTracesGroup = TraceClientCore::CModule::Instance().TracesGroupMgr().CreateTracesGroup( pChannel->Name() );
    pTracesGroup->AddChannel(pChannel);
}

