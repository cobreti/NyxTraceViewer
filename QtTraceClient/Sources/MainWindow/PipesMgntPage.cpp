#include "PipesMgntPage.hpp"
#include "PipesMgntPageItemDelegate.hpp"
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
m_pDoc(NULL),
m_pItemDelegate(NULL)
{
    ui->setupUi(this);

    setWindowFlags( Qt::Widget );

    connect(ui->m_btnAdd, SIGNAL(clicked()), this, SLOT(OnNewPool()));
    connect(ui->m_PoolsTree, SIGNAL(itemSelectionChanged()), this, SLOT(OnPoolSelectionChanged()));
	connect(ui->m_PoolsTree, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(OnPoolItemChanged(QTreeWidgetItem*, int)));
	connect(ui->m_PoolsTree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(OnPoolItemClicked(QTreeWidgetItem*, int)));
    connect(ui->m_PoolsTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(OnPoolItemDoubleClicked(QTreeWidgetItem*, int)));

    ui->m_btnRemove->setEnabled(false);

    QIcon                                       PipeSourceIcon(":/MainWindow/Icons/PipeSource-icon.png");
    QIcon                                       StateIcon(":/MainWindow/Icons/StartPipe-icon.png");

    ui->m_PoolsTree->setColumnWidth(0, 48);
    ui->m_PoolsTree->setColumnWidth(1, 48 );
    ui->m_PoolsTree->setColumnWidth(2, 48 );


    m_pItemDelegate = new CPipesMgntPageItemDelegate();
    m_pItemDelegate->SetTreeWidget( ui->m_PoolsTree );
    ui->m_PoolsTree->setItemDelegateForColumn(0, m_pItemDelegate);
    ui->m_PoolsTree->setItemDelegateForColumn(1, m_pItemDelegate);
    ui->m_PoolsTree->setItemDelegateForColumn(2, m_pItemDelegate);
    ui->m_PoolsTree->setItemDelegateForColumn(3, m_pItemDelegate);
}


/**
 *
 */
CPipesMgntPage::~CPipesMgntPage()
{
    delete m_pItemDelegate;
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
    QIcon                                       StateIcon(":/MainWindow/Icons/StartPipe-icon.png");

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
    //pItem->setIcon(0, PipeSourceIcon);
    //pItem->setIcon(1, StateIcon);
    ui->m_PoolsTree->insertTopLevelItem(ui->m_PoolsTree->topLevelItemCount(), pItem );
    ui->m_PoolsTree->clearSelection();
    pItem->setSelected(true);
    pItem->setCheckState(0, Qt::Checked);

    m_pDoc->AddRepositorySrc(*refPool);
}


/**
 *
 */
void CPipesMgntPage::OnPoolItemChanged( QTreeWidgetItem* pItem, int )
{
	MainWindow::CPoolTreeItem*		pPoolItem = static_cast<MainWindow::CPoolTreeItem*>(pItem);

    if ( pPoolItem->TraceChannel() && pPoolItem->TraceChannel()->Name() != pItem->text(3).toStdString().c_str() )
    {
        Nyx::CAString            AnsiName( pItem->text(3).toStdString().c_str() );
        Nyx::CWString            WName;
        
        WName = AnsiName;

        pPoolItem->TraceChannel()->Name() = AnsiName; //pItem->text(0).toStdString().c_str();

        TraceClientCore::CModule&			rModule = TraceClientCore::CModule::Instance();
        rModule.TraceChannels().Update( pPoolItem->TraceChannel() );

        pPoolItem->TraceChannel()->Pool()->SetName( WName.c_str() );
        rModule.TracesPools().Update(pPoolItem->TraceChannel()->Pool());
    }
}


/**
 *
 */
void CPipesMgntPage::OnPoolItemClicked( QTreeWidgetItem* pItem, int column )
{
	MainWindow::CPoolTreeItem*		pPoolItem = static_cast<MainWindow::CPoolTreeItem*>(pItem);

    if ( column == 0 )
    {
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
}


/**
 *
 */
void CPipesMgntPage::OnPoolItemDoubleClicked( QTreeWidgetItem* pItem, int column )
{
	MainWindow::CPoolTreeItem*		pPoolItem = static_cast<MainWindow::CPoolTreeItem*>(pItem);

    if ( column == 2 )
    {
        TraceClientCore::CTraceChannel*     pChannel = pPoolItem->TraceChannel();

        if ( pChannel->Feeder().Valid() )
		{
            if ( pChannel->Feeder()->IsRunning() )
			{
                pChannel->Feeder()->Stop();
				pItem->setFlags( Qt::ItemIsEditable | pItem->flags() );
				pItem->setForeground(0, QBrush(QColor(150, 0, 0)));
			}
			else
			{
                pChannel->Feeder()->Start();
				pItem->setFlags( pItem->flags() & ~Qt::ItemIsEditable );
				pItem->setForeground(0, QBrush(QColor(0, 150, 0)));
			}
		}
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
}
