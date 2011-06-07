#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DebugPanel.h"
#include "TracesDocument.hpp"
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
    delete m_pViewPage;
    delete ui;
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
        m_pViewPage->show(pViewItem->View());
    else
        m_pViewPage->hide();
}


/**
 *
 */
void CMainWindow::OnAddView()
{
    CTracesDocument*                 pDocument = NULL;

    if ( ui->m_ViewsTree->selectedItems().empty() )
    {
        pDocument = CreateNewDocument( QString("Document ") + QString().setNum(m_nNextDocumentId++) );
    }
    else
    {
        MainWindow::CViewTreeItem*       pCurrentItem = static_cast<MainWindow::CViewTreeItem*>(ui->m_ViewsTree->selectedItems().front());
        pDocument = &pCurrentItem->View()->Doc();
    }

    CreateNewView(pDocument, QString("View ") + QString().setNum(m_nNextViewId++));
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
CTracesView* CMainWindow::CreateNewView( CTracesDocument* pDoc, const QString& ViewName )
{
	CTracesView*					pView = pDoc->CreateView(m_pViewPage);
    QIcon                           ViewIcon(":/MainWindow/Icons/View-icon.png");

	pView->SetName(ViewName);

    MainWindow::CViewTreeItem*          pViewItem = new MainWindow::CViewTreeItem(NULL, pView);
    pViewItem->setFlags( Qt::ItemIsEditable | pViewItem->flags() );
    pViewItem->setIcon(0, ViewIcon);
    pViewItem->setSelected(true);

    ui->m_ViewsTree->addTopLevelItem( pViewItem );

    m_pViewPage->show(pView);

    return pView;
}
