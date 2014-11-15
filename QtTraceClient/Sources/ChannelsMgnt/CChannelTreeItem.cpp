#include "TraceChannel.hpp"

#include "CChannelTreeItem.hpp"


/**
 *
 */
CChannelTreeItem::CChannelTreeItem() : QTreeWidgetItem(),
    m_pChannel(NULL)
{
    setCheckState(1, Qt::Unchecked);
}


/**
 *
 */
CChannelTreeItem::~CChannelTreeItem()
{
}


/**
 *
 */
void CChannelTreeItem::SetChannel( TraceClientCore::CTraceChannel* pChannel )
{
    m_pChannel = pChannel;

//    QString     name = pChannel->Name().c_str();

    setText(2, pChannel->Name());
}
