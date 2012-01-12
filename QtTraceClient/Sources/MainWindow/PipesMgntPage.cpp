#include "PipesMgntPage.hpp"
#include "ui_PipesMgntPage.h"
#include "MainWindow/PoolTreeItem.hpp"
#include "TraceClientCoreModule.hpp"
#include "PipeTraceFeeder.hpp"
#include "Document/TracesDocument.hpp"
#include "PoolsUpdateClock.hpp"
#include "DataStruct/PoolsList.hpp"
#include "TraceChannel.hpp"


/**
 *
 */
CPipesMgntPage::CPipesMgntPage(QWidget* pParent) :
QDialog(pParent),
ui(new Ui::PipesMgntPage()),
m_pDoc(NULL)
{
    ui->setupUi(this);

    setWindowFlags( Qt::Widget );

    connect(ui->m_btnAdd, SIGNAL(clicked()), this, SLOT(OnNewPool()));
    connect(ui->m_btnStartStop, SIGNAL(clicked()), this, SLOT(OnStartStop()));
    connect(ui->m_PoolsTree, SIGNAL(itemSelectionChanged()), this, SLOT(OnPoolSelectionChanged()));
	connect(ui->m_PoolsTree, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(OnPoolItemChanged(QTreeWidgetItem*, int)));
	connect(ui->m_PoolsTree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(OnPoolItemClicked(QTreeWidgetItem*, int)));

    ui->m_btnRemove->setEnabled(false);
    ui->m_btnStartStop->setIcon(QIcon(":/MainWindow/Icons/StartPipe-icon.png"));
    ui->m_btnStartStop->setEnabled(false);
}


/**
 *
 */
void CPipesMgntPage::show(CTracesDocument* pDoc)
{
    if ( NULL == pDoc )
        return;

    m_pDoc = pDoc;

    FillPoolsList();

    QDialog::show();
}


/**
 *
 */
void CPipesMgntPage::Refresh()
{
    FillPoolsList();
}


/**
 *
 */
void CPipesMgntPage::OnNewPool()
{
	TraceClientCore::CTracesPoolRef				refPool;
	MainWindow::CPoolTreeItem*					pItem = new MainWindow::CPoolTreeItem();
    TraceClientCore::CPipeTraceFeeder*          pPipeTraceFeeder = NULL;
	TraceClientCore::CModule&					rModule = TraceClientCore::CModule::Instance();
    QIcon                                       PipeSourceIcon(":/MainWindow/Icons/PipeSource-icon.png");

    //
    // Add pool
    //

    refPool = new TraceClientCore::CTracesPool(Nyx::CMemoryPool::Alloc(1024*1024), L"new pool");
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
	pItem->setForeground( 0, QBrush(QColor(150, 0, 0)) );
    pItem->setIcon(0, PipeSourceIcon);
    ui->m_PoolsTree->insertTopLevelItem(ui->m_PoolsTree->topLevelItemCount(), pItem );
    ui->m_PoolsTree->clearSelection();
    pItem->setSelected(true);
    pItem->setCheckState(0, Qt::Checked);

    m_pDoc->AddRepositorySrc(*refPool);
}


/**
 *
 */
void CPipesMgntPage::OnStartStop()
{
	MainWindow::CPoolTreeItem*		pItem = static_cast<MainWindow::CPoolTreeItem*>(ui->m_PoolsTree->selectedItems().front());
    QIcon                           StartPipeIcon(":/MainWindow/Icons/StartPipe-icon.png");
    QIcon                           StopPipeIcon(":/MainWindow/Icons/StopPipe-icon.png");

	if ( pItem != NULL )
	{
        TraceClientCore::CTraceChannel* pChannel = pItem->TraceChannel();

        if ( pChannel->Feeder().Valid() )
		{
            if ( pChannel->Feeder()->IsRunning() )
			{
                pChannel->Feeder()->Stop();
				pItem->setFlags( Qt::ItemIsEditable | pItem->flags() );
				pItem->setForeground(0, QBrush(QColor(150, 0, 0)));
                ui->m_btnStartStop->setIcon(StartPipeIcon);
			}
			else
			{
                pChannel->Feeder()->Start();
				pItem->setFlags( pItem->flags() & ~Qt::ItemIsEditable );
				pItem->setForeground(0, QBrush(QColor(0, 150, 0)));
                ui->m_btnStartStop->setIcon(StopPipeIcon);
			}
		}
	}
}


/**
 *
 */
void CPipesMgntPage::OnPoolSelectionChanged()
{
    if ( ui->m_PoolsTree->selectedItems().empty() )
        return;

	MainWindow::CPoolTreeItem*		pItem = static_cast<MainWindow::CPoolTreeItem*>(ui->m_PoolsTree->selectedItems().front());
    QIcon                           StartPipeIcon(":/MainWindow/Icons/StartPipe-icon.png");
    QIcon                           StopPipeIcon(":/MainWindow/Icons/StopPipe-icon.png");

	if ( pItem == NULL )
	{
        ui->m_btnStartStop->setIcon(StartPipeIcon);
		ui->m_btnStartStop->setEnabled(false);
	}
	else
	{
        TraceClientCore::CTraceChannel*     pChannel = pItem->TraceChannel();

        if ( !pChannel->Feeder().Valid() )
		{
            ui->m_btnStartStop->setIcon(StartPipeIcon);
			ui->m_btnStartStop->setEnabled(false);
		}
		else
		{
            if ( pChannel->Feeder()->IsRunning() )
			{
                ui->m_btnStartStop->setIcon(StopPipeIcon);
				ui->m_btnStartStop->setEnabled(true);
			}
			else
			{
                ui->m_btnStartStop->setIcon(StartPipeIcon);
				ui->m_btnStartStop->setEnabled(true);
			}
		}
	}
}


/**
 *
 */
void CPipesMgntPage::OnPoolItemChanged( QTreeWidgetItem* pItem, int )
{
	MainWindow::CPoolTreeItem*		pPoolItem = static_cast<MainWindow::CPoolTreeItem*>(pItem);

    if ( pPoolItem->TraceChannel() && pPoolItem->TraceChannel()->Name() != pItem->text(0).toStdString().c_str() )
    {
        pPoolItem->TraceChannel()->Name() = pItem->text(0).toStdString().c_str();

        TraceClientCore::CModule&			rModule = TraceClientCore::CModule::Instance();
        rModule.TraceChannels().Update( pPoolItem->TraceChannel() );
    }
}


/**
 *
 */
void CPipesMgntPage::OnPoolItemClicked( QTreeWidgetItem* pItem, int  )
{
	MainWindow::CPoolTreeItem*		pPoolItem = static_cast<MainWindow::CPoolTreeItem*>(pItem);

	if ( pPoolItem->checkState(0) == Qt::Checked )
	{
        if ( !m_pDoc->Contains( *pPoolItem->TraceChannel()->Pool() ) )
            m_pDoc->AddRepositorySrc(*pPoolItem->TraceChannel()->Pool());
	}
	else if ( pPoolItem->checkState(0) == Qt::Unchecked )
	{
        if ( m_pDoc->Contains( *pPoolItem->TraceChannel()->Pool() ) )
            m_pDoc->RemoveRepositorySrc(*pPoolItem->TraceChannel()->Pool());
	}
}


/**
 *
 */
void CPipesMgntPage::FillPoolsList()
{
    TraceClientCore::CModule&                               rModule = TraceClientCore::CModule::Instance();
    QIcon                                                   PipeSourceIcon(":/MainWindow/Icons/PipeSource-icon.png");
    TraceClientCore::CTraceChannelsList                     ChannelsList;
    TraceClientCore::CTraceChannelsList::const_iterator     ChannelPos;

    rModule.TraceChannels().GetChannelsList(ChannelsList);

    ui->m_PoolsTree->clear();

    for ( ChannelPos = ChannelsList.begin(); ChannelPos != ChannelsList.end(); ++ ChannelPos )
    {
        MainWindow::CPoolTreeItem*                  pItem = new MainWindow::CPoolTreeItem();
        TraceClientCore::CTraceChannel&       rChannel = (*ChannelPos).Channel();

        pItem->SetChannel( &rChannel );
	    pItem->setFlags( Qt::ItemIsEditable | pItem->flags() );
	    pItem->setForeground( 0, QBrush(QColor(150, 0, 0)) );
        pItem->setIcon(0, PipeSourceIcon);

        if ( rChannel.Feeder().Valid() )
        {
            if ( rChannel.Feeder()->IsRunning() )
			{
				pItem->setFlags( pItem->flags() & ~Qt::ItemIsEditable );
				pItem->setForeground(0, QBrush(QColor(0, 150, 0)));
			}
			else
			{
				pItem->setFlags( Qt::ItemIsEditable | pItem->flags() );
				pItem->setForeground(0, QBrush(QColor(150, 0, 0)));
			}
        }

        if ( m_pDoc->Contains(*rChannel.Pool()) )
            pItem->setCheckState(0, Qt::Checked );
        else
            pItem->setCheckState(0, Qt::Unchecked );

        ui->m_PoolsTree->insertTopLevelItem(ui->m_PoolsTree->topLevelItemCount(), pItem );
    }

    ui->m_btnStartStop->setEnabled(false);
}
