#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DebugPanel.h"
#include "Document/TracesDocument.hpp"
#include "Dialogs/NewPoolDlg.hpp"
#include "Dialogs/NewDocumentDlg.hpp"
#include "Dialogs/NewViewDlg.hpp"
#include "MainWindow/ViewTreeItem.hpp"
#include "MainWindow/ViewPage.hpp"
#include "PipeTraceFeeder.hpp"
#include "PoolsUpdateClock.hpp"

#include <QCloseEvent>
#include <QDesktopWidget>
#include <QResizeEvent>
#include <QFile>

/**
 *
 */
CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_pDebugPanel(NULL),
    m_nNextDocumentId(1),
    m_nNextViewId(1),
    m_pViewPage(NULL)
{
    ui->setupUi(this);

    connect(ui->m_ViewsTree, SIGNAL(itemSelectionChanged()), this, SLOT(OnViewsTreeSelectionChanged()));
    connect(ui->m_btnAddView, SIGNAL(clicked()), this, SLOT(OnAddView()));
    connect(ui->m_btnCopyView, SIGNAL(clicked()), this, SLOT(OnCopyView()));
    connect(ui->m_ViewsTree, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(OnViewItemChanged(QTreeWidgetItem*, int )));

    m_pViewPage = new CViewPage(ui->m_ContentFrame);
    ui->m_ContentFrame->layout()->addWidget(m_pViewPage);

	QRect rcDesktop = QApplication::desktop()->availableGeometry();

	this->move( rcDesktop.x(), rcDesktop.y() );

    TraceClientCore::CModule&                   rModule = TraceClientCore::CModule::Instance();
    TraceClientCore::CTracesPoolRef             refTracesPool = rModule.TracesPools()[L"QtDefault"];

    rModule.PoolsUpdateClock().Start();

    //m_pDebugPanel = new CDebugPanel(this);
    //m_pDebugPanel->setParent(NULL, Qt::Window);
    //m_pDebugPanel->show();

    //m_pDefaultDocument = new CTracesRepositoryDoc(this, "");
    //m_pDefaultDocument->Init();

    //CreateDocViewRoot();

    refTracesPool = rModule.TracesPools()[L"TracesPipe"];
    CTracesDocument* pNewDoc = CreateNewDocument( QString("Document ") + QString().setNum(m_nNextDocumentId++) );

	// create view
	CTracesView* pView = CreateNewView( pNewDoc, QString("View ") + QString().setNum(m_nNextViewId++) );

    ui->m_btnRemove->setEnabled(false);
}


/**
 *
 */
CMainWindow::~CMainWindow()
{
    delete m_pViewPage;
    delete ui;
}


/**
 *
 */
void CMainWindow::PinView( CTracesView* pView )
{
    QWidget*        pViewParent = static_cast<QWidget*>(pView->parent());
    
    m_pViewPage->show(pView);

    SelectItemWithView(pView);
}


/**
 *
 */
void CMainWindow::UnpinView( CTracesView* pView )
{
    CViewPage*      pViewPage = new CViewPage(NULL);

    pViewPage->show(pView);
    m_pViewPage->DetachView(pView);
}



/**
 *
 */
void CMainWindow::OnViewsTreeSelectionChanged()
{
    if ( ui->m_ViewsTree->selectedItems().empty() )
        return;

    MainWindow::CViewTreeItem*      pViewItem = static_cast<MainWindow::CViewTreeItem*>(ui->m_ViewsTree->selectedItems().front());

    if ( pViewItem )
    {
        CTracesView*        pView = pViewItem->View();

        if ( pView )
        {
            QWidget*            pParent = pView->topLevelWidget();

            if ( pParent != this )
            {
                pParent->activateWindow();
                pParent->setFocus();
            }
            else
                m_pViewPage->show(pView);
        }
    }
    else
        m_pViewPage->hide();

    ui->m_btnCopyView->setEnabled( pViewItem->parent() == NULL);
}


/**
 *
 */
void CMainWindow::OnAddView()
{
    CTracesDocument*                 pDocument = NULL;

//    if ( ui->m_ViewsTree->selectedItems().empty() )
//    {
        pDocument = CreateNewDocument( QString("Document ") + QString().setNum(m_nNextDocumentId++) );
//    }
//    else
//    {
//        MainWindow::CViewTreeItem*       pCurrentItem = static_cast<MainWindow::CViewTreeItem*>(ui->m_ViewsTree->selectedItems().front());
//        pDocument = &pCurrentItem->View()->Doc();
//    }

    CreateNewView(pDocument, QString("View ") + QString().setNum(m_nNextViewId++));
}


/**
 *
 */
void CMainWindow::OnCopyView()
{
    CTracesDocument*                 pDocument = NULL;

    MainWindow::CViewTreeItem*       pCurrentItem = static_cast<MainWindow::CViewTreeItem*>(ui->m_ViewsTree->selectedItems().front());
    pDocument = &pCurrentItem->View()->Doc();

    CreateNewView(pDocument, QString("View ") + QString().setNum(m_nNextViewId++), pCurrentItem);
}


/**
 *
 */
void CMainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


/**
 *
 */
void CMainWindow::closeEvent(QCloseEvent* e)
{
    TraceClientCore::CModule::Instance().PoolsUpdateClock().Stop();

    int     count = ui->m_ViewsTree->topLevelItemCount();

    for (int index = 0; index < count; ++index)
    {
        MainWindow::CViewTreeItem*      pViewItem = static_cast<MainWindow::CViewTreeItem*>(ui->m_ViewsTree->topLevelItem(index));

        if ( pViewItem->View()->topLevelWidget() != this )
            pViewItem->View()->topLevelWidget()->close();

        CloseChildViews(pViewItem);
    }

    m_Documents.Clear();

	e->accept();
}


void CMainWindow::CloseChildViews( QTreeWidgetItem* pParent )
{
    int     count = pParent->childCount();

    for (int index = 0; index < count; ++index)
    {
        MainWindow::CViewTreeItem*      pViewItem = static_cast<MainWindow::CViewTreeItem*>(pParent->child(index));

        if ( pViewItem->View()->topLevelWidget() != this )
            pViewItem->View()->topLevelWidget()->close();
    }
}


/**
 *
 */
void CMainWindow::OnViewItemChanged( QTreeWidgetItem* pItem, int )
{
    MainWindow::CViewTreeItem*      pViewItem = static_cast<MainWindow::CViewTreeItem*>(pItem);

    pViewItem->View()->SetName( pViewItem->text(0) );
}


/**
 *
 */
CTracesDocument* CMainWindow::CreateNewDocument( const QString& rDocumentName )
{
    CTracesDocument*                pDocument = new CTracesDocument(this, rDocumentName);
	pDocument->Init();

	m_Documents.Insert( Nyx::CAString(rDocumentName.toStdString().c_str()), pDocument );

	return pDocument;
}


/**
 *
 */
CTracesView* CMainWindow::CreateNewView( CTracesDocument* pDoc, const QString& ViewName, QTreeWidgetItem* pParent /*= NULL*/ )
{
	CTracesView*					pView = pDoc->CreateView(m_pViewPage);
    QIcon                           ViewIcon(":/MainWindow/Icons/View-icon.png");

	pView->SetName(ViewName);

    MainWindow::CViewTreeItem*          pParentViewItem = static_cast<MainWindow::CViewTreeItem*>(pParent);
    MainWindow::CViewTreeItem*          pViewItem = new MainWindow::CViewTreeItem(pParent, pView);
    pViewItem->setFlags( Qt::ItemIsEditable | pViewItem->flags() );
    pViewItem->setIcon(0, ViewIcon);

    ui->m_ViewsTree->clearSelection();

    if ( pParentViewItem )
    {
        pView->InitFromView( *pParentViewItem->View() );
        ui->m_ViewsTree->expandItem(pParentViewItem);
        pParentViewItem->addChild(pViewItem);
        pViewItem->setSelected(true);
//        m_pViewPage->hide();
    }
    else
    {
        ui->m_ViewsTree->addTopLevelItem( pViewItem );
        pViewItem->setSelected(true);
    }

    PinView(pView);
    //ui->m_ViewsTree->setCurrentItem(pViewItem, 1);

    //m_pViewPage->show(pView);

    return pView;
}


/**
 *
 */
void CMainWindow::SelectItemWithView( CTracesView* pView )
{
    int     count = ui->m_ViewsTree->topLevelItemCount();

    ui->m_ViewsTree->clearSelection();

    for (int index = 0; index < count; ++index)
    {
        MainWindow::CViewTreeItem*      pViewItem = static_cast<MainWindow::CViewTreeItem*>(ui->m_ViewsTree->topLevelItem(index));

        if ( pViewItem->View() == pView )
        {
            pViewItem->setSelected(true);
            break;
        }
    }
}
