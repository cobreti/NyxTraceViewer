#include "TracesWindow.hpp"
#include "TracesView.h"
#include "ChannelSelection.h"
#include "MainWindow/PipesMgntPage.hpp"
#include "MainWindow/MainWindow.hpp"
#include "TraceClientApp.h"
#include "WindowsManager.hpp"
#include "TraceChannel.hpp"
#include "TraceClientCoreModule.hpp"
#include "PoolsUpdateClock.hpp"

#include "ui_TracesWindow.h"
#include "ChannelsMgnt/ChannelsMgnt.hpp"
#include "View/ViewSearchEngine.h"
#include "Dialogs/AboutDlg.h"
#include "Dialogs/HighlightColorsSelectionDlg.h"
#include "View/Highlight/HighlightsMgrWnd.h"
#include "View/Decorations/DynamicTextHighlight.h"

#include "Color/ColorBtn.h"


#include <QToolButton>
#include <QCloseEvent>
#include <QFileDialog>
#include <QLineEdit>
#include <QKeyEvent>


//QMainWindow*        CTracesWindow::s_pDummyWnd = NULL;


/**
 *
 */
CTracesWindow::CTracesWindow(CTracesWindow *pSrc) : QMainWindow(),
    ui( new Ui::TracesWindow() ),
    m_pTracesView(NULL),
    m_pChannelSelection(NULL),
    m_pBtn_MainWindow(NULL),
    m_pBtn_SourceFeeds(NULL),
    m_pBtn_NewView(NULL),
    m_pBtn_CloneView(NULL),
    m_pBtn_Search(NULL),
    m_pBtn_HighlightColorSelection(NULL),
    m_pBtn_SaveAs(NULL),
    m_pBtn_About(NULL),
    m_pBtn_Settings(NULL),
    m_pBtn_Devices(NULL),
    m_pSearchText(NULL),
    m_pBtn_HideSearch(NULL),
    m_pBtn_SearchNext(NULL),
    m_pBtn_SearchPrevious(NULL),
    m_pBtn_HighlightColor(NULL),
    m_pPipesMgntPage(NULL),
    m_pSearchEngine(NULL),
    m_pHighlightsMgrWnd(NULL)
{
    ui->setupUi(this);

//    if ( s_pDummyWnd == NULL )
//    {
//        s_pDummyWnd = new QMainWindow();
//    }

//    setParent( s_pDummyWnd, Qt::Window );

    QIcon               MainWindowIcon(":/TracesWindow/MainWindow");
    QIcon               PipeSourceIcon(":/TracesWindow/Icons/PipeSource-icon.png");
    QIcon               NewViewIcon(":/TracesWindow/Icons/View-icon.png");
    QIcon               CloneViewIcon(":/TracesWindow/Icons/View-Copy-icon.png");
    QIcon               SaveAsIcon(":/TracesWindow/Icons/SaveAs.png");
    QIcon               AboutIcon(":/TracesWindow/About");
    QIcon               SearchNextIcon(":/TracesWindow/SearchNext");
    QIcon               SearchPreviousIcon(":/TracesWindow/SearchPrevious");
    QIcon               HighlightColorSelectionIcon(":/TracesWindow/HighlightColorSelection");
    QIcon               SearchIcon(":/TracesWindow/Search");
    QIcon               HideSearchIcon(":/TracesWindow/HideSearch");
    QIcon               SettingsIcon(":/TracesWindow/Settings-Icon");
    QIcon               SettingsSelectedIcon(":/TracesWindow/Settings-Selected-Icon");
    QIcon               DevicesIcon(":/TracesWindow/Device-Icon");
    QIcon               DevicesSelectedIcon(":/TracesWindow/Device-Selected-Icon");
    QIcon               Clear(":/TracesWindow/Clear-Icon");

    CTracesView* pBase = NULL;

    if ( pSrc )
        pBase = pSrc->m_pTracesView;

    m_pTracesView = new CTracesView(this, pBase);
    m_pChannelSelection = new CChannelSelection(this);
//    m_pPipesMgntPage = new CPipesMgntPage(this);
//    m_pPipesMgntPage->hide();

    ui->gridLayout->addWidget(m_pChannelSelection, 0, 1);
    ui->gridLayout->addWidget(m_pTracesView, 0, 2);

    m_pBtn_MainWindow = new QToolButton();
    m_pBtn_MainWindow->setIcon(MainWindowIcon);

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

    m_pBtn_Clear = new QToolButton();
    m_pBtn_Clear->setIcon(Clear);

    m_pBtn_About = new QToolButton();
    m_pBtn_About->setIcon(AboutIcon);

    m_pBtn_Settings = new CToggleToolButton();
    m_pBtn_Settings->setNormalIcon(SettingsIcon);
    m_pBtn_Settings->setSelectedIcon(SettingsSelectedIcon);

    m_pBtn_Devices = new CToggleToolButton();
    m_pBtn_Devices->setNormalIcon(DevicesIcon);
    m_pBtn_Devices->setSelectedIcon(DevicesSelectedIcon);

    m_pSearchText = new QLineEdit();
    
    m_pBtn_SearchNext = new QToolButton();
    m_pBtn_SearchNext->setEnabled(false);
    m_pBtn_SearchNext->setIcon(SearchNextIcon);

    m_pBtn_SearchPrevious = new QToolButton();
    m_pBtn_SearchPrevious->setEnabled(false);
    m_pBtn_SearchPrevious->setIcon(SearchPreviousIcon);

    m_pBtn_HideSearch = new QToolButton();
    m_pBtn_HideSearch->setIcon(HideSearchIcon);
    m_pBtn_HideSearch->setEnabled(false);

    m_pBtn_HighlightColor = new CChooseColorBtn();

//    ui->MainToolBar->addWidget(m_pBtn_MainWindow);
    ui->MainToolBar->addWidget(m_pBtn_Settings);
    ui->MainToolBar->addWidget(m_pBtn_Devices);
    ui->MainToolBar->addSeparator();
//    ui->MainToolBar->addWidget(m_pBtn_SourceFeeds);
//    ui->MainToolBar->addSeparator();
//    ui->MainToolBar->addWidget(m_pBtn_NewView);
//    ui->MainToolBar->addWidget(m_pBtn_CloneView);
//    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addWidget(m_pBtn_Search);
    ui->MainToolBar->addWidget(m_pBtn_HighlightColorSelection);
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addWidget(m_pBtn_SaveAs);
    ui->MainToolBar->addWidget(m_pBtn_Clear);
//    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addWidget(m_pBtn_About);
    ui->MainToolBar->setIconSize( QSize(16, 16) );

    ui->SearchToolBar->addWidget(m_pBtn_HighlightColor);
    ui->SearchToolBar->addWidget(m_pSearchText);
    ui->SearchToolBar->addWidget(m_pBtn_SearchNext);
    ui->SearchToolBar->addWidget(m_pBtn_SearchPrevious);
    ui->SearchToolBar->addWidget(m_pBtn_HideSearch);
    ui->SearchToolBar->setIconSize( QSize(16, 16) );

    connect( m_pBtn_SourceFeeds, SIGNAL(clicked()), this, SLOT(OnSourceFeedsBtnClicked()));
    connect( m_pBtn_NewView, SIGNAL(clicked()), this, SLOT(OnNewView()));
    connect( m_pBtn_CloneView, SIGNAL(clicked()), this, SLOT(OnCloneView()));
    connect( m_pBtn_SaveAs, SIGNAL(clicked()), this, SLOT(OnSaveAs()));
    connect( m_pBtn_Clear, SIGNAL(clicked()), this, SLOT(OnClear()));
    connect( m_pSearchText, SIGNAL(textChanged(const QString&)), this, SLOT(OnSearchTextChanged(const QString&)));
    connect( m_pBtn_SearchNext, SIGNAL(clicked()), this, SLOT(OnSearchNext()));
    connect( m_pBtn_SearchPrevious, SIGNAL(clicked()), this, SLOT(OnSearchPrevious()));
    connect( m_pBtn_HideSearch, SIGNAL(clicked()), this, SLOT(OnHideSearch()));
    connect( m_pBtn_HighlightColor, SIGNAL(OnColorChanged(CColorBtn*)), this, SLOT(OnHighlightColorChanged(CColorBtn*)));
    connect( m_pBtn_About, SIGNAL(clicked()), this, SLOT(OnAbout()));
    connect( m_pBtn_HighlightColorSelection, SIGNAL(clicked()), this, SLOT(OnHighlightColorSelection()));
    connect( m_pBtn_Search, SIGNAL(clicked()), this, SLOT(OnSearch()));
    connect( m_pBtn_MainWindow, SIGNAL(clicked()), this, SLOT(OnShowMainWindow()));
    connect( m_pChannelSelection, SIGNAL(SelectionChanged(TraceClientCore::CTracesGroup*)),
             this, SLOT(OnTracesGroupSelectionChanged(TraceClientCore::CTracesGroup*)) );
    connect( m_pBtn_Settings, SIGNAL(stateChanged(CToggleToolButton::EState)), this, SLOT(OnSettingsBtnStateChanged(CToggleToolButton::EState)));
    connect( m_pBtn_Devices, SIGNAL(stateChanged(CToggleToolButton::EState)), this, SLOT(OnDevicesSelectionBtnStateChanged(CToggleToolButton::EState)));

    CWindowsManager::Instance().AddTracesWindow(this);

    m_pSearchEngine = new CViewSearchEngine(*m_pTracesView);

    m_pHighlightsMgrWnd = new CHighlightsMgrWnd(m_pSearchEngine, this);

    m_refHighlighter = new CViewItemHighlighter();
    m_refTextPattern = new CViewItemPattern_Text();
    m_refHighlighter->Pattern() = (CViewItemPattern*)m_refTextPattern;

    m_pTracesView->Highlighters()->Add( m_refHighlighter );

    m_WndName = QString::number(CWindowsManager::Instance().TracesWindows().GetWindowNo());

    CDynamicHighlight*  pHighlight = m_pTracesView->dynamicHighlights().Get(CDynamicHighlight::kDefault);
    CDynamicTextHighlight*  pTextHighlight = static_cast<CDynamicTextHighlight*>(pHighlight);
    m_pBtn_HighlightColor->Color() = pTextHighlight->color();

    QString     title;
    title += "NyxTracesViewer - ";
    title += m_WndName;
    title += " -      v";
    title += CTraceClientApp::Instance().GetVersion();
    setWindowTitle(title);

    m_pHighlightsMgrWnd->setWindowTitle( "Highlights - " + m_WndName);
}


/**
 *
 */
CTracesWindow::~CTracesWindow()
{
    delete m_pHighlightsMgrWnd;
    delete m_pSearchEngine;

    CWindowsManager::Instance().TracesWindows().Remove(this);
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
    pWnd->showNormal();
}


/**
 *
 */
void CTracesWindow::OnCloneView()
{
    CTracesWindow* pWnd = new CTracesWindow(this);
    pWnd->showNormal();
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


void CTracesWindow::OnClear()
{
    m_pTracesView->Clear();
    m_pTracesView->focusedItem() = CViewTracesIterator();
    m_pBtn_SearchNext->setEnabled( false );
    m_pBtn_SearchPrevious->setEnabled( false );
}


/**
 *
 */
void CTracesWindow::OnSearchTextChanged( const QString& text )
{
    CDynamicHighlight*  pHighlight = m_pTracesView->dynamicHighlights().Get(CDynamicHighlight::kDefault);
    CDynamicTextHighlight*  pTextHighlight = static_cast<CDynamicTextHighlight*>(pHighlight);

    pTextHighlight->text() = text;

    m_pTracesView->focusedItem().setText(text);
    m_pBtn_SearchNext->setEnabled( !text.isEmpty() && m_pTracesView->topPos().Valid() );
    m_pBtn_SearchPrevious->setEnabled( !text.isEmpty() && m_pTracesView->topPos().Valid() );

    m_pTracesView->update();
}


/**
 *
 */
void CTracesWindow::OnSearchNext()
{
    CViewTracesContentIterator&  rPos =  m_pTracesView->focusedItem();

    if ( !rPos.Valid() )
    {
        rPos = m_pTracesView->FirstPos();
    }

    ++ rPos;

    m_pBtn_SearchPrevious->setEnabled( !m_pSearchText->text().isEmpty() && m_pTracesView->topPos().Valid() );
    m_pBtn_SearchNext->setEnabled( !m_pSearchText->text().isEmpty() && m_pTracesView->topPos().Valid() );

    m_pTracesView->MakeFocusedItemVisible();
    m_pTracesView->update();
}


/**
 *
 */
void CTracesWindow::OnSearchPrevious()
{
    CViewTracesContentIterator&  rPos =  m_pTracesView->focusedItem();

    if ( !rPos.Valid() )
    {
        rPos = m_pTracesView->LastPos();
        rPos.moveToEnd();
    }

    -- rPos;

    m_pBtn_SearchPrevious->setEnabled( !m_pSearchText->text().isEmpty() && m_pTracesView->topPos().Valid() );
    m_pBtn_SearchNext->setEnabled( !m_pSearchText->text().isEmpty() && m_pTracesView->topPos().Valid() );
    m_pTracesView->MakeFocusedItemVisible();
    m_pTracesView->update();
}


/**
 *
 */
void CTracesWindow::OnHighlightColorChanged(CColorBtn* pBtn)
{
    CDynamicHighlight*  pHighlight = m_pTracesView->dynamicHighlights().Get(CDynamicHighlight::kDefault);
    CDynamicTextHighlight*  pTextHighlight = static_cast<CDynamicTextHighlight*>(pHighlight);

    pTextHighlight->color() = pBtn->Color();
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
    QPoint              pt( frameGeometry().right()+1, frameGeometry().top() );

    m_pHighlightsMgrWnd->Show(pt, QSize(0, rect().height()));
}


/**
 *
 */
void CTracesWindow::OnHideSearch()
{
    m_pSearchEngine->Clear();

    m_pBtn_HideSearch->setEnabled(false);
}


/**
 *
 */
void CTracesWindow::OnShowMainWindow()
{
    CTraceClientApp::Instance().MainWindow()->showNormal();
    CTraceClientApp::Instance().MainWindow()->activateWindow();
}


/**
 * @brief CTracesWindow::OnTracesGroupSelectionChanged
 * @param pGroup
 */
void CTracesWindow::OnTracesGroupSelectionChanged(TraceClientCore::CTracesGroup* pGroup)
{
    m_pTracesView->SetTracesGroup(pGroup);
}


void CTracesWindow::OnSettingsBtnStateChanged(CToggleToolButton::EState state)
{
    switch (state)
    {
    case CToggleToolButton::eState_Normal:
        CTraceClientApp::Instance().HideSettings();
        break;

    case CToggleToolButton::eState_Selected:
        CTraceClientApp::Instance().ShowSettings(this, QPoint(20, ui->MainToolBar->height()));
        break;
    }
}


void CTracesWindow::OnDevicesSelectionBtnStateChanged(CToggleToolButton::EState state)
{
    switch (state)
    {
    case CToggleToolButton::eState_Normal:
        CTraceClientApp::Instance().HideDevicesSelection();
        break;

    case CToggleToolButton::eState_Selected:
        CTraceClientApp::Instance().ShowDevicesSelection(this, QPoint(50, ui->MainToolBar->height()));
        break;
    }
}


/**
 *
 */
void CTracesWindow::closeEvent(QCloseEvent *event)
{
    NYXTRACE(0x0, L"CTracesWindow::closeEvent");

    CWindowsManager::Instance().OnWindowClosing(this);

    destroy();
    delete this;
}


/**
 *
 */
void CTracesWindow::showEvent(QShowEvent *)
{
    if ( isMinimized() )
    {
        NYXTRACE(0x0, L"CTracesWindow::showEvent - minimized");
    }
    else
    {
        NYXTRACE(0x0, L"CTracesWindow::showEvent");
    }

    CWindowsManager::Instance().OnShowWindow(this);
}


/**
 *
 */
void CTracesWindow::hideEvent(QHideEvent *)
{
    if ( isMinimized() )
    {
        NYXTRACE(0x0, L"CTracesWindow::hideEvent - minimized");
    }
    else
    {
        NYXTRACE(0x0, L"CTracesWindow::hideEvent");
    }

    CWindowsManager::Instance().OnHideWindow(this);
}


/**
 *
 */
void CTracesWindow::moveEvent(QMoveEvent* pEvent)
{
    CWindowsManager::Instance().OnWindowMoved(this, pEvent->pos());
}
