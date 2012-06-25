#include "TracesWindow.hpp"
#include "TracesView.h"
#include "MainWindow/PipesMgntPage.hpp"
#include "MainWindow/MainWindow.hpp"
#include "TraceClientApp.h"
#include "TraceChannel.hpp"
#include "TraceClientCoreModule.hpp"
#include "PoolsUpdateClock.hpp"

#include "ui_TracesWindow.h"
#include "ChannelsMgnt/ChannelsMgnt.hpp"
#include "View/ViewSearchEngine.h"
#include "Dialogs/AboutDlg.h"
#include "Dialogs/HighlightColorsSelectionDlg.h"
#include "View/Highlight/HighlightsMgrWnd.h"

#include "Color/ColorBtn.h"

#include <QToolButton>
#include <QCloseEvent>
#include <QFileDialog>
#include <QLineEdit>


QMainWindow*        CTracesWindow::s_pDummyWnd = NULL;


/**
 *
 */
CTracesWindow::CTracesWindow(CTracesWindow *pSrc) : QMainWindow(),
    ui( new Ui::TracesWindow() ),
    m_pTracesView(NULL),
    m_pBtn_SourceFeeds(NULL),
    m_pBtn_NewView(NULL),
    m_pBtn_CloneView(NULL),
    m_pBtn_Search(NULL),
    m_pBtn_HighlightColorSelection(NULL),
    m_pBtn_SaveAs(NULL),
    m_pBtn_About(NULL),
    m_pSearchText(NULL),
    m_pBtn_SearchNext(NULL),
    m_pBtn_SearchPrevious(NULL),
    m_pBtn_HighlightColor(NULL),
    m_pPipesMgntPage(NULL),
    m_pSearchEngine(NULL),
    m_pHighlightsMgrWnd(NULL)
{
    ui->setupUi(this);

    if ( s_pDummyWnd == NULL )
    {
        s_pDummyWnd = new QMainWindow();
    }

    setParent( s_pDummyWnd, Qt::Window );

    QIcon               PipeSourceIcon(":/TracesWindow/Icons/PipeSource-icon.png");
    QIcon               NewViewIcon(":/TracesWindow/Icons/View-icon.png");
    QIcon               CloneViewIcon(":/TracesWindow/Icons/View-Copy-icon.png");
    QIcon               SaveAsIcon(":/TracesWindow/Icons/SaveAs.png");
    QIcon               AboutIcon(":/TracesWindow/About");
    QIcon               SearchNextIcon(":/TracesWindow/SearchNext");
    QIcon               SearchPreviousIcon(":/TracesWindow/SearchPrevious");
    QIcon               HighlightColorSelectionIcon(":/TracesWindow/HighlightColorSelection");
    QIcon               SearchIcon(":/TracesWindow/Search");

    CTracesView* pBase = NULL;

    if ( pSrc )
        pBase = pSrc->m_pTracesView;

    m_pTracesView = new CTracesView(this, pBase);
    m_pPipesMgntPage = new CPipesMgntPage(this);
    m_pPipesMgntPage->hide();

    ui->gridLayout->addWidget(m_pPipesMgntPage);
    ui->gridLayout->addWidget(m_pTracesView);

    m_pBtn_SourceFeeds = new QToolButton();
    m_pBtn_SourceFeeds->setIcon(PipeSourceIcon);
//    m_pBtn_SourceFeeds->setCheckable(true);

    m_pBtn_NewView = new QToolButton();
    m_pBtn_NewView->setIcon(NewViewIcon);

    m_pBtn_CloneView = new QToolButton();
    m_pBtn_CloneView->setIcon(CloneViewIcon);

    m_pBtn_Search = new QToolButton();
    m_pBtn_Search->setIcon(SearchIcon);

    m_pBtn_HighlightColorSelection = new QToolButton();
    m_pBtn_HighlightColorSelection->setIcon(HighlightColorSelectionIcon);

    m_pBtn_SaveAs = new QToolButton();
    m_pBtn_SaveAs->setIcon(SaveAsIcon);

    m_pBtn_About = new QToolButton();
    m_pBtn_About->setIcon(AboutIcon);

    m_pSearchText = new QLineEdit();
    
    m_pBtn_SearchNext = new QToolButton();
    m_pBtn_SearchNext->setEnabled(false);
    m_pBtn_SearchNext->setIcon(SearchNextIcon);

    m_pBtn_SearchPrevious = new QToolButton();
    m_pBtn_SearchPrevious->setEnabled(false);
    m_pBtn_SearchPrevious->setIcon(SearchPreviousIcon);

    m_pBtn_HighlightColor = new CChooseColorBtn();

    ui->MainToolBar->addWidget(m_pBtn_SourceFeeds);
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addWidget(m_pBtn_NewView);
    ui->MainToolBar->addWidget(m_pBtn_CloneView);
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addWidget(m_pBtn_Search);
    ui->MainToolBar->addWidget(m_pBtn_HighlightColorSelection);
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addWidget(m_pBtn_SaveAs);
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addWidget(m_pBtn_About);
    ui->MainToolBar->setIconSize( QSize(16, 16) );

    ui->SearchToolBar->addWidget(m_pBtn_HighlightColor);
    ui->SearchToolBar->addWidget(m_pSearchText);
    ui->SearchToolBar->addWidget(m_pBtn_SearchNext);
    ui->SearchToolBar->addWidget(m_pBtn_SearchPrevious);
    ui->SearchToolBar->setIconSize( QSize(16, 16) );

    connect( m_pBtn_SourceFeeds, SIGNAL(clicked()), this, SLOT(OnSourceFeedsBtnClicked()));
    connect( m_pBtn_NewView, SIGNAL(clicked()), this, SLOT(OnNewView()));
    connect( m_pBtn_CloneView, SIGNAL(clicked()), this, SLOT(OnCloneView()));
    connect( m_pBtn_SaveAs, SIGNAL(clicked()), this, SLOT(OnSaveAs()));
    connect( m_pSearchText, SIGNAL(textChanged(const QString&)), this, SLOT(OnSearchTextChanged(const QString&)));
    connect( m_pBtn_SearchNext, SIGNAL(clicked()), this, SLOT(OnSearchNext()));
    connect( m_pBtn_SearchPrevious, SIGNAL(clicked()), this, SLOT(OnSearchPrevious()));
    connect( m_pBtn_HighlightColor, SIGNAL(OnColorChanged(CColorBtn*)), this, SLOT(OnHighlightColorChanged(CColorBtn*)));
    connect( m_pBtn_About, SIGNAL(clicked()), this, SLOT(OnAbout()));
    connect( m_pBtn_HighlightColorSelection, SIGNAL(clicked()), this, SLOT(OnHighlightColorSelection()));
    connect( m_pBtn_Search, SIGNAL(clicked()), this, SLOT(OnSearch()));

    CTraceClientApp::Instance().TracesWindows().Insert(this);

    m_pSearchEngine = new CViewSearchEngine(*m_pTracesView);

    m_pHighlightsMgrWnd = new CHighlightsMgrWnd(m_pTracesView, this);
}


/**
 *
 */
CTracesWindow::~CTracesWindow()
{
    delete m_pHighlightsMgrWnd;
    delete m_pSearchEngine;

    CTraceClientApp::Instance().TracesWindows().Remove(this);
}


/**
 *
 */
void CTracesWindow::OnSourceFeedsBtnClicked()
{
    QPoint              pt( m_pBtn_SourceFeeds->frameGeometry().left(), m_pBtn_SourceFeeds->frameGeometry().bottom() );

    pt = mapToGlobal(pt);

    CChannelsMgnt::Show(this, pt, m_pTracesView->ViewCore());
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
void CTracesWindow::OnSaveAs()
{
    QFileDialog     fileDlg(this);

    fileDlg.setNameFilter(tr("text (*.txt)"));
    fileDlg.setAcceptMode( QFileDialog::AcceptSave );
    fileDlg.setViewMode( QFileDialog::Detail);

    if ( fileDlg.exec())
    {
        QString     file = fileDlg.selectedFiles()[0];

        m_pTracesView->Save(file);
    }
}


/**
 *
 */
void CTracesWindow::OnSearchTextChanged( const QString& text )
{
    m_pBtn_SearchNext->setEnabled( !text.isEmpty() );
    m_pBtn_SearchPrevious->setEnabled( !text.isEmpty() );

    m_pSearchEngine->SetText(text);
    m_pTracesView->update();
}


/**
 *
 */
void CTracesWindow::OnSearchNext()
{
    m_pSearchEngine->Next();
}


/**
 *
 */
void CTracesWindow::OnSearchPrevious()
{
    m_pSearchEngine->Previous();
}


/**
 *
 */
void CTracesWindow::OnHighlightColorChanged(CColorBtn* pBtn)
{
    m_pSearchEngine->Highlighter()->HighlightColor() = pBtn->Color();
    m_pTracesView->update();
}


/**
 *
 */
void CTracesWindow::OnAbout()
{
    CAboutDlg   dlg(this);

    dlg.exec();
}


/**
 *
 */
void CTracesWindow::OnHighlightColorSelection()
{
    CHighlightColorsSelectionDlg        dlg(CTraceClientApp::Instance().AppSettings().ViewHighlightSettings(), this);

    dlg.exec();
}


/**
 *
 */
void CTracesWindow::OnSearch()
{
    //QPoint              pt( m_pBtn_SourceFeeds->frameGeometry().left(), m_pBtn_SourceFeeds->frameGeometry().bottom() );
    QPoint              pt( frameGeometry().right()+1, frameGeometry().top() );

    //pt = mapToGlobal(pt);

    m_pHighlightsMgrWnd->Show(pt, QSize(0, rect().height()));
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
