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
    connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(onAddChannel()));
    connect(ui->newChannelEdit, SIGNAL(textChanged(QString)), this, SLOT(onNewChannelNameChanged(QString)));

    ui->addBtn->setEnabled(false);
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


void CChannelSelection::onAddChannel()
{
    QString         channelName = ui->newChannelEdit->text();
    Nyx::CAString   strChannelName(channelName.toStdString().c_str());

    TraceClientCore::CModule&           rModule = TraceClientCore::CModule::Instance();
    TraceClientCore::CTracesGroupMgr&   rTracesGroupMgr = rModule.TracesGroupMgr();

    rTracesGroupMgr.CreateTracesGroup(strChannelName);

    ui->addBtn->setEnabled(false);
}


void CChannelSelection::onNewChannelNameChanged(const QString &text)
{
    Nyx::CAString                       strChannelName(text.toStdString().c_str());
    TraceClientCore::CModule&           rModule = TraceClientCore::CModule::Instance();
    TraceClientCore::CTracesGroupMgr&   rTracesGroupMgr = rModule.TracesGroupMgr();
    bool                                bChannelNameValid = !text.isEmpty() && (NULL == rTracesGroupMgr.GetGroup(strChannelName));

    ui->addBtn->setEnabled(bChannelNameValid);
}
