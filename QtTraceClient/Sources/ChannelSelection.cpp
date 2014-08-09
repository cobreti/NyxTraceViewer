#include <Nyx.hpp>

#include "ChannelSelection.h"
#include "TracesGroupListItem.h"
#include "ui_ChannelSelection.h"
#include "TraceClientCoreModule.hpp"
#include "TracesGroupMgr.hpp"


CChannelSelection::CChannelSelection(QWidget* pParent) :
QWidget(pParent),
ui(new Ui::ChannelSelection() )
{
    ui->setupUi(this);

    connect(ui->channelsList, SIGNAL(itemSelectionChanged()), this, SLOT(onChannelSelectionChanged()));
    connect(&m_ChannelsListener, SIGNAL(newChannel(TraceClientCore::CTraceChannel*)), this, SLOT(onNewChannel(TraceClientCore::CTraceChannel*)));
    connect(&m_TracesGroupListener, SIGNAL(NewTracesGroup(TraceClientCore::CTracesGroup*)), this, SLOT(onNewTracesGroup(TraceClientCore::CTracesGroup*)));
}


CChannelSelection::~CChannelSelection()
{
}


void CChannelSelection::onChannelSelectionChanged()
{
    QListWidgetItem* item = ui->channelsList->selectedItems()[0];
    CTracesGroupListItem* pGroupItem = static_cast<CTracesGroupListItem*>(item);

    QString text = item->text();

    emit SelectionChanged(pGroupItem->Group());
}


void CChannelSelection::onNewChannel(TraceClientCore::CTraceChannel* pChannel)
{

}


void CChannelSelection::onNewTracesGroup(TraceClientCore::CTracesGroup *pGroup)
{
    CTracesGroupListItem*   pItem = new CTracesGroupListItem(pGroup, ui->channelsList);
    ui->channelsList->addItem(pItem);
}

