#include "TraceClientCoreModule.hpp"
#include "PipeTraceFeeder.hpp"
#include "PoolsUpdateClock.hpp"
#include "DataStruct/PoolsList.hpp"
#include "View/TracesViewCore.hpp"

#include "ui_ChannelsMgnt.h"
#include "ChannelsMgnt.hpp"
#include "ChannelsMgnt/CChannelTreeItem.hpp"
#include "ChannelsMgnt/CChannelTreeItemDelegate.hpp"
#include "ChannelsMgnt/CClearChannelContentConfirmationDlg.hpp"



CChannelsMgnt*  CChannelsMgnt::s_pInstance = NULL;


/**
 *
 */
void CChannelsMgnt::Show( QWidget* pParent, const QPoint& pt, CTracesViewCore* pViewCore )
{
    if ( NULL == s_pInstance )
        s_pInstance = new CChannelsMgnt();

    s_pInstance->Init(pParent, pt, pViewCore);
}


/**
 *
 */
CChannelsMgnt::CChannelsMgnt() :
    QWidget(NULL),
    ui(new Ui::ChannelsMgnt),
    m_pChannelTreeItemDelegate(NULL),
    m_pViewCore(NULL),
    m_NextChannelNumber(1)
{
    ui->setupUi(this);

    setWindowFlags( Qt::Popup );

    m_pChannelTreeItemDelegate = new CChannelTreeItemDelegate();
    m_pChannelTreeItemDelegate->SetTreeWidget( ui->ChannelsTreeWidget );
    ui->ChannelsTreeWidget->setItemDelegateForColumn(0, m_pChannelTreeItemDelegate);
    ui->ChannelsTreeWidget->setItemDelegateForColumn(1, m_pChannelTreeItemDelegate);
    ui->ChannelsTreeWidget->setItemDelegateForColumn(2, m_pChannelTreeItemDelegate);
    ui->ChannelsTreeWidget->setItemDelegateForColumn(3, m_pChannelTreeItemDelegate);
    ui->ChannelsTreeWidget->setItemDelegateForColumn(4, m_pChannelTreeItemDelegate);

    connect(ui->btnAddChannel, SIGNAL(clicked()), this, SLOT(OnNewChannel()));
    connect(ui->ChannelsTreeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(OnChannelItemChanged(QTreeWidgetItem*, int)));
    connect(ui->ChannelsTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(OnChannelItemClicked(QTreeWidgetItem*, int)));
    connect(ui->ChannelsTreeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(OnChannelItemDoubleClicked(QTreeWidgetItem*, int)));
}


/**
 *
 */
CChannelsMgnt::~CChannelsMgnt()
{
    delete ui;
}


/**
 *
 */
void CChannelsMgnt::OnNewChannel()
{
    TraceClientCore::CTracesPoolRef				refPool;
    CChannelTreeItem*                           pItem = new CChannelTreeItem();
    TraceClientCore::CPipeTraceFeeder*          pPipeTraceFeeder = NULL;
    TraceClientCore::CModule&					rModule = TraceClientCore::CModule::Instance();
    QString                                     channelName;
//    Nyx::CWString                               channelName(50);

    channelName = QString("Channel %1").arg( QString::number(m_NextChannelNumber) );
//    channelName.Format(L"Channel_%i", m_NextChannelNumber);
    ++m_NextChannelNumber;

    //
    // Add pool
    //

    refPool = new TraceClientCore::CTracesPool(Nyx::CMemoryPool::Alloc(10 * 1024*1024), channelName);
    rModule.TracesPools().Add(refPool);
    rModule.PoolsUpdateClock().Insert(refPool);


    //
    // Add channel
    //

    TraceClientCore::CTraceChannel*      pChannel = new TraceClientCore::CTraceChannel(refPool);
    pChannel->Name() = refPool->Name();
    rModule.TraceChannels().Add(pChannel);

    //
    // Add Pipe Feeder
    //

    pPipeTraceFeeder = new TraceClientCore::CPipeTraceFeeder( pChannel );
    pChannel->Feeder() = pPipeTraceFeeder;

    //
    // Add gui item
    //

    pItem->SetChannel(pChannel);
    pItem->setFlags( Qt::ItemIsEditable | pItem->flags() );
    pItem->setForeground( 2, QBrush(QColor(150, 0, 0)) );
    ui->ChannelsTreeWidget->insertTopLevelItem(ui->ChannelsTreeWidget->topLevelItemCount(), pItem );
    ui->ChannelsTreeWidget->clearSelection();

    if ( m_pViewCore != NULL )
    {
        pItem->setSelected(true);
        pItem->setCheckState(1, Qt::Checked);

        m_pViewCore->AddRepository(*refPool);
    }
}


/**
 *
 */
void CChannelsMgnt::OnChannelItemChanged( QTreeWidgetItem* pItem, int )
{
    CChannelTreeItem*       pChannelItem = static_cast<CChannelTreeItem*>(pItem);

    if ( pChannelItem->TraceChannel() && pChannelItem->TraceChannel()->Name() != pItem->text(2).toStdString().c_str() )
    {
        QString                 name = pItem->text(2);
//        Nyx::CAString            AnsiName( pItem->text(2).toStdString().c_str() );
//        Nyx::CWString            WName;

//        WName = AnsiName;

        pChannelItem->TraceChannel()->Name() = name;

        TraceClientCore::CModule&			rModule = TraceClientCore::CModule::Instance();
        rModule.TraceChannels().Update( pChannelItem->TraceChannel() );

        pChannelItem->TraceChannel()->Pool()->SetName( name );
        rModule.TracesPools().Update(pChannelItem->TraceChannel()->Pool());
    }
}


/**
 *
 */
void CChannelsMgnt::OnChannelItemClicked( QTreeWidgetItem* pItem, int column )
{
    CChannelTreeItem*		pChannelItem = static_cast<CChannelTreeItem*>(pItem);

    if ( column == 1 )
    {
        if ( pChannelItem->checkState(1) == Qt::Checked )
        {
            if ( m_pViewCore != NULL && !m_pViewCore->Contains( *pChannelItem->TraceChannel()->Pool() ) )
                m_pViewCore->AddRepository(*pChannelItem->TraceChannel()->Pool());
        }
        else if ( pChannelItem->checkState(1) == Qt::Unchecked )
        {
            if ( m_pViewCore != NULL && m_pViewCore->Contains( *pChannelItem->TraceChannel()->Pool() ) )
                m_pViewCore->RemoveRepository(*pChannelItem->TraceChannel()->Pool());
        }
    }
}


/**
 *
 */
void CChannelsMgnt::OnChannelItemDoubleClicked( QTreeWidgetItem* pItem, int column )
{
    CChannelTreeItem*		pChannelItem = static_cast<CChannelTreeItem*>(pItem);

    if ( column == 3 )
    {
        TraceClientCore::CTraceChannel*     pChannel = pChannelItem->TraceChannel();

        if ( pChannel->Feeder().Valid() )
        {
            if ( pChannel->Feeder()->IsRunning() )
            {
                pChannel->Feeder()->Stop();
                pItem->setFlags( Qt::ItemIsEditable | pItem->flags() );
                pItem->setForeground(2, QBrush(QColor(150, 0, 0)));
            }
            else
            {
                pChannel->Feeder()->Start();
                pItem->setFlags( pItem->flags() & ~Qt::ItemIsEditable );
                pItem->setForeground(2, QBrush(QColor(0, 150, 0)));
            }
        }
    }
    else if ( column == 4 )
    {
        EmptyChannel(pChannelItem->TraceChannel());
    }
}


/**
 *
 */
void CChannelsMgnt::Init( QWidget* pParent, const QPoint& pt, CTracesViewCore* pViewCore )
{
    m_pViewCore = pViewCore;
    setWindowFlags(Qt::Popup);
    LoadChannels();

    move(pt);
    show();
}


/**
 *
 */
void CChannelsMgnt::LoadChannels()
{
    TraceClientCore::CModule&                               rModule = TraceClientCore::CModule::Instance();
    TraceClientCore::CTraceChannelsList                     ChannelsList;
    TraceClientCore::CTraceChannelsList::const_iterator     ChannelPos;

    rModule.TraceChannels().GetChannelsList(ChannelsList);

    ui->ChannelsTreeWidget->clear();

    for ( ChannelPos = ChannelsList.begin(); ChannelPos != ChannelsList.end(); ++ ChannelPos )
    {
        CChannelTreeItem*                           pItem = new CChannelTreeItem();
        TraceClientCore::CTraceChannel&             rChannel = (*ChannelPos).Channel();

        pItem->SetChannel( &rChannel );
        pItem->setForeground( 2, QBrush(QColor(150, 0, 0)) );

        if ( rChannel.Feeder().Valid() )
        {
            if ( rChannel.Feeder()->IsRunning() )
            {
                pItem->setFlags( pItem->flags() & ~Qt::ItemIsEditable );
                pItem->setForeground(2, QBrush(QColor(0, 150, 0)));
            }
            else
            {
                if ( m_pViewCore != NULL )
                    pItem->setFlags( Qt::ItemIsEditable | pItem->flags() );

                pItem->setForeground(2, QBrush(QColor(150, 0, 0)));
            }
        }

        if ( m_pViewCore != NULL )
        {
            if ( m_pViewCore->Contains(*rChannel.Pool()) )
                pItem->setCheckState(1, Qt::Checked );
            else
                pItem->setCheckState(1, Qt::Unchecked );
        }

        ui->ChannelsTreeWidget->insertTopLevelItem(ui->ChannelsTreeWidget->topLevelItemCount(), pItem );
    }
}


/**
 *
 */
void CChannelsMgnt::showEvent(QShowEvent *pEvent)
{
    QRect       rcRow = ui->ChannelsTreeWidget->rect();

    int         ChannelIconWidth = 32;
    int         CheckStatusIconWidth = 48;
    int         TextWidth = 200;
    int         StartStopIconWidth = 32;
    int         EmptyIconWidth = 32;

    if ( m_pViewCore == NULL )
        CheckStatusIconWidth = 0;

    TextWidth = rcRow.width()
                - ChannelIconWidth
                - CheckStatusIconWidth
                - StartStopIconWidth
                - EmptyIconWidth;

    ui->ChannelsTreeWidget->setColumnWidth(0, ChannelIconWidth);
    ui->ChannelsTreeWidget->setColumnWidth(1, CheckStatusIconWidth );
    ui->ChannelsTreeWidget->setColumnWidth(2, TextWidth );
    ui->ChannelsTreeWidget->setColumnWidth(3, StartStopIconWidth );
    ui->ChannelsTreeWidget->setColumnWidth(4, EmptyIconWidth );
}


/**
 *
 */
void CChannelsMgnt::EmptyChannel(TraceClientCore::CTraceChannel* pChannel)
{
    CClearChannelContentConfirmationDlg     dlg(pChannel->Name(), this);

    dlg.exec();

    if ( CClearChannelContentConfirmationDlg::eDlgRes_Empty == dlg.Result() )
    {
        bool bWasRunning = pChannel->Feeder().Valid() && pChannel->Feeder()->IsRunning();

        if ( bWasRunning )
            pChannel->Feeder()->Stop();

        TraceClientCore::CModule::Instance().PoolsUpdateClock().Stop();

        pChannel->Clear();

        TraceClientCore::CModule::Instance().PoolsUpdateClock().Start();

        if ( bWasRunning )
            pChannel->Feeder()->Start();
    }
}

