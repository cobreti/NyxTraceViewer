#include "PipesMgntPage.hpp"
#include "ui_PipesMgntPage.h"
#include "MainWindow/PoolTreeItem.hpp"
#include "TraceClientCoreModule.hpp"
#include "PipeTraceFeeder.hpp"
#include "TracesDocument.hpp"
#include "PoolsUpdateClock.hpp"


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

    for (int index = 0; index < ui->m_PoolsTree->topLevelItemCount(); ++index)
    {
        MainWindow::CPoolTreeItem*		pPoolItem = static_cast<MainWindow::CPoolTreeItem*>(ui->m_PoolsTree->topLevelItem(index));

        if ( m_pDoc->Contains(*pPoolItem->TracesPool()) )
            pPoolItem->setCheckState(0, Qt::Checked );
        else
            pPoolItem->setCheckState(0, Qt::Unchecked );
    }

    QDialog::show();
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

    refPool = new TraceClientCore::CTracesPool(Nyx::CMemoryPool::Alloc(1024*1024), L"new pool");
	rModule.TracesPools().Add(refPool);
    rModule.PoolsUpdateClock().Insert(refPool);

    pPipeTraceFeeder = new TraceClientCore::CPipeTraceFeeder( refPool);
	refPool->Feeder() = pPipeTraceFeeder;

	pItem->SetPool(refPool);
	pItem->setFlags( Qt::ItemIsEditable | pItem->flags() );
	pItem->setForeground( 0, QBrush(QColor(150, 0, 0)) );
    pItem->setIcon(0, PipeSourceIcon);
    ui->m_PoolsTree->insertTopLevelItem(ui->m_PoolsTree->topLevelItemCount(), pItem );
    ui->m_PoolsTree->clearSelection();
    pItem->setSelected(true);
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
		TraceClientCore::CTracesPool* pPool = pItem->TracesPool();

		if ( pPool->Feeder().Valid() )
		{
			if ( pPool->Feeder()->IsRunning() )
			{
				pPool->Feeder()->Stop();
				pItem->setFlags( Qt::ItemIsEditable | pItem->flags() );
				pItem->setForeground(0, QBrush(QColor(150, 0, 0)));
                ui->m_btnStartStop->setIcon(StartPipeIcon);
			}
			else
			{
				pPool->SetName( pItem->text(0).toStdWString().c_str() );
				pPool->Feeder()->Start();
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
		TraceClientCore::CTracesPool*		pPool = pItem->TracesPool();

		if ( !pPool->Feeder().Valid() )
		{
            ui->m_btnStartStop->setIcon(StartPipeIcon);
			ui->m_btnStartStop->setEnabled(false);
		}
		else
		{
			if ( pPool->Feeder()->IsRunning() )
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

	if ( pPoolItem->TracesPool()->Name() != Nyx::CWString(pItem->text(0).toStdWString().c_str()) )
	{
		pPoolItem->TracesPool()->SetName( pItem->text(0).toStdWString().c_str() );
		TraceClientCore::CModule&			rModule = TraceClientCore::CModule::Instance();

		rModule.TracesPools().Update(pPoolItem->TracesPool());
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
		//CTracesRepositoryDoc*		pCurrentDoc = SelectedDocument();

		if ( !m_pDoc->Contains( *pPoolItem->TracesPool() ) )
			m_pDoc->AddRepositorySrc(*pPoolItem->TracesPool());
	}
	else if ( pPoolItem->checkState(0) == Qt::Unchecked )
	{
		//CTracesRepositoryDoc*		pCurrentDoc = SelectedDocument();

		if ( m_pDoc->Contains( *pPoolItem->TracesPool() ) )
			m_pDoc->RemoveRepositorySrc(*pPoolItem->TracesPool());
	}
}
