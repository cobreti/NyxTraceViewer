#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DebugPanel.h"
#include "TracesDocument.hpp"
#include "Dialogs/NewPoolDlg.hpp"
#include "Dialogs/NewDocumentDlg.hpp"
#include "Dialogs/NewViewDlg.hpp"
//#include "MainWindow/PoolTreeItem.hpp"
//#include "MainWindow/DocListItem.hpp"
//#include "MainWindow/ViewListItem.hpp"
#include "MainWindow/DocViewTreeItem.hpp"
#include "MainWindow/PipesMgntPage.hpp"
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
    m_pPipesMgntPage(NULL),
    m_pViewPage(NULL)
{
    ui->setupUi(this);

    connect(ui->m_DocsViewsTree, SIGNAL(itemSelectionChanged()), this, SLOT(OnDocsViewsTreeSelectionChanged()));
    connect(ui->m_btnAddDocument, SIGNAL(clicked()), this, SLOT(OnAddDoc()));
    connect(ui->m_btnAddView, SIGNAL(clicked()), this, SLOT(OnAddView()));

    m_pPipesMgntPage = new CPipesMgntPage(ui->m_ContentFrame);
    ui->m_ContentFrame->layout()->addWidget(m_pPipesMgntPage);

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
	CreateNewView( pNewDoc, QString("View ") + QString().setNum(m_nNextViewId++) );

    ui->m_btnRemove->setEnabled(false);
}


/**
 *
 */
CMainWindow::~CMainWindow()
{
    delete m_pPipesMgntPage;
    delete m_pViewPage;
    delete ui;
}


/**
 *
 */
void CMainWindow::OnDocsViewsTreeSelectionChanged()
{
    if ( ui->m_DocsViewsTree->selectedItems().empty() )
        return;

    MainWindow::CDocViewTreeItem*      pDocViewItem = static_cast<MainWindow::CDocViewTreeItem*>(ui->m_DocsViewsTree->selectedItems().front());

    if ( pDocViewItem->Type() == MainWindow::CDocViewTreeItem::eCT_Document )
    {
        m_pPipesMgntPage->show(pDocViewItem->Document());
        m_pViewPage->hide();
    }
    else if ( pDocViewItem->Type() == MainWindow::CDocViewTreeItem::eCT_View )
    {
        m_pPipesMgntPage->hide();
        m_pViewPage->show(pDocViewItem->View());
    }
    else
    {
        m_pPipesMgntPage->hide();
        m_pViewPage->hide();
    }
}


/**
 *
 */
void CMainWindow::OnAddDoc()
{
    CreateNewDocument(QString("Document ") + QString().setNum(m_nNextDocumentId++));
}


/**
 *
 */
void CMainWindow::OnAddView()
{
    MainWindow::CDocViewTreeItem*       pCurrentItem = static_cast<MainWindow::CDocViewTreeItem*>(ui->m_DocsViewsTree->selectedItems().front());    

    CreateNewView(pCurrentItem->Document(), QString("View ") + QString().setNum(m_nNextViewId++));
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

    m_Documents.Clear();

	e->accept();
}


/**
 *
 */
void CMainWindow::CreateDocViewRoot()
{
    MainWindow::CDocViewTreeItem*       pTreeItem = new MainWindow::CDocViewTreeItem(NULL, "Root");
    ui->m_DocsViewsTree->addTopLevelItem(pTreeItem);
    ui->m_DocsViewsTree->clearSelection();
    pTreeItem->setSelected(true);
    pTreeItem->setExpanded(true);
}


/**
 *
 */
CTracesDocument* CMainWindow::CreateNewDocument( const QString& rDocumentName )
{
    CTracesDocument*                pDocument = new CTracesDocument(this, rDocumentName);
    QIcon                           DocIcon(":/MainWindow/Icons/Document-icon.png");
	pDocument->Init();

	m_Documents.Insert( Nyx::CAString(rDocumentName.toStdString().c_str()), pDocument );

    MainWindow::CDocViewTreeItem*                   pTreeItem = new MainWindow::CDocViewTreeItem(NULL, pDocument);
    pTreeItem->setFlags( Qt::ItemIsEditable | pTreeItem->flags() );
    pTreeItem->setIcon(0, DocIcon);
    ui->m_DocsViewsTree->addTopLevelItem( pTreeItem );
    ui->m_DocsViewsTree->clearSelection();
    pTreeItem->setSelected(true);

	return pDocument;
}


/**
 *
 */
CTracesView* CMainWindow::CreateNewView( CTracesDocument* pDoc, const QString& ViewName )
{
	CTracesView*					pView = pDoc->CreateView(NULL);
    QIcon                           ViewIcon(":/MainWindow/Icons/View-icon.png");

	pView->SetName(ViewName);

    MainWindow::CDocViewTreeItem*       pParentTreeItem = static_cast<MainWindow::CDocViewTreeItem*>(ui->m_DocsViewsTree->selectedItems()[0]);

    if ( pParentTreeItem->Type() == MainWindow::CDocViewTreeItem::eCT_View )
        pParentTreeItem = static_cast<MainWindow::CDocViewTreeItem*>(pParentTreeItem->parent());

    MainWindow::CDocViewTreeItem*       pTreeItem = new MainWindow::CDocViewTreeItem(pParentTreeItem, pDoc, pView);

    pTreeItem->setFlags( Qt::ItemIsEditable | pTreeItem->flags() );
    pTreeItem->setIcon(0, ViewIcon);
    ui->m_DocsViewsTree->clearSelection();
    pTreeItem->setSelected(true);
    pParentTreeItem->setExpanded(true);

    pView->show();

	return pView;
}
