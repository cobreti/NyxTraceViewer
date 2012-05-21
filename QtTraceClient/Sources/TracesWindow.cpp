#include "TracesWindow.hpp"
#include "TracesView.h"
#include "MainWindow/PipesMgntPage.hpp"
#include "TraceClientApp.h"

#include "ui_TracesWindow.h"

#include <QToolButton>
#include <QCloseEvent>


/**
 *
 */
CTracesWindow::CTracesWindow(CTracesWindow *pSrc) : QMainWindow(),
ui( new Ui::TracesWindow() ),
m_pTracesView(NULL),
m_pBtn_SourceFeeds(NULL),
m_pPipesMgntPage(NULL)
{
    ui->setupUi(this);

    QIcon               PipeSourceIcon(":/TracesWindow/Icons/PipeSource-icon.png");
    QIcon               NewViewIcon(":/TracesWindow/Icons/View-icon.png");
    QIcon               CloneViewIcon(":/TracesWindow/Icons/View-Copy-icon.png");

    CTracesView* pBase = NULL;

    if ( pSrc )
        pBase = pSrc->m_pTracesView;

    m_pTracesView = new CTracesView(this, pBase);
    m_pPipesMgntPage = new CPipesMgntPage(this);
    m_pPipesMgntPage->hide();

    ui->gridLayout->addWidget(m_pPipesMgntPage);
    ui->gridLayout->addWidget(m_pTracesView);

    m_pBtn_SourceFeeds = new QToolButton();
    m_pBtn_SourceFeeds->setIconSize( QSize(32, 32) );
    m_pBtn_SourceFeeds->setIcon(PipeSourceIcon);
    m_pBtn_SourceFeeds->setCheckable(true);

    m_pBtn_NewView = new QToolButton();
    m_pBtn_NewView->setIcon(NewViewIcon);

    m_pBtn_CloneView = new QToolButton();
    m_pBtn_CloneView->setIcon(CloneViewIcon);

    ui->toolBar->addWidget(m_pBtn_SourceFeeds);
    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(m_pBtn_NewView);
    ui->toolBar->addWidget(m_pBtn_CloneView);

    connect( m_pBtn_SourceFeeds, SIGNAL(clicked()), this, SLOT(OnSourceFeedsBtnClicked()));
    connect( m_pBtn_NewView, SIGNAL(clicked()), this, SLOT(OnNewView()));
    connect( m_pBtn_CloneView, SIGNAL(clicked()), this, SLOT(OnCloneView()));

    CTraceClientApp::Instance().TracesWindows().Insert(this);
}


/**
 *
 */
CTracesWindow::~CTracesWindow()
{
    CTraceClientApp::Instance().TracesWindows().Remove(this);
}


/**
 *
 */
void CTracesWindow::OnSourceFeedsBtnClicked()
{
    if ( m_pBtn_SourceFeeds->isChecked() )
    {
        m_pPipesMgntPage->show(m_pTracesView->ViewCore());
        //m_pTracesView->hide();
    }
    else
    {
        m_pPipesMgntPage->hide();
        //m_pTracesView->show();
    }
}


/**
 *
 */
void CTracesWindow::OnNewView()
{
    CTracesWindow* pWnd =  new CTracesWindow(NULL);
    pWnd->show();
}


/**
 *
 */
void CTracesWindow::OnCloneView()
{
    CTracesWindow* pWnd = new CTracesWindow(this);
    pWnd->show();
}


/**
 *
 */
void CTracesWindow::closeEvent(QCloseEvent *event)
{
    m_pTracesView->close();
    delete m_pTracesView;

    event->accept();
    delete this;
}
