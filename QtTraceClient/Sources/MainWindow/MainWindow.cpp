#include "MainWindow.hpp"
#include "TracesWindow.hpp"
#include "ChannelsMgnt/ChannelsMgnt.hpp"
#include "Dialogs/AboutDlg.h"
#include "TraceClientApp.h"
#include "TraceClientCoreModule.hpp"


#include <QToolButton>
#include <QCloseEvent>

#include "TcpIpSettingsPanel.h"
#include "ui_MainWindow.h"


/**
 *
 */
CMainWindow::CMainWindow() : QMainWindow(),
    ui( new Ui::MainWindow()),
    m_pBtn_NewView(NULL),
    m_pBtn_Channels(NULL),
    m_pBtn_About(NULL)
{
    ui->setupUi(this);

    QIcon       NewViewIcon(":/MainWindow/Icons/View-icon.png");
    QIcon       ChannelsIcon(":/MainWindow/Icons/PipeSource-icon.png");
    QIcon       AboutIcon(":/MainWindow/About");

    m_pBtn_NewView = new QToolButton();
    m_pBtn_NewView->setIcon(NewViewIcon);

    m_pBtn_Channels = new QToolButton();
    m_pBtn_Channels->setIcon(ChannelsIcon);

    m_pBtn_About = new QToolButton();
    m_pBtn_About->setIcon(AboutIcon);

    ui->MainToolBar->addWidget(m_pBtn_Channels);
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addWidget(m_pBtn_NewView);
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addWidget(m_pBtn_About);
    ui->MainToolBar->setIconSize( QSize(16, 16) );

    connect( m_pBtn_NewView, SIGNAL(clicked()), this, SLOT(OnNewTracesWindow()));
    connect( m_pBtn_Channels, SIGNAL(clicked()), this, SLOT(OnChannelsMgnt()));
    connect( m_pBtn_About, SIGNAL(clicked()), this, SLOT(OnAbout()));

    QString     title = windowTitle();
    title += "     v";
    title += CTraceClientApp::Instance().GetVersion();
    setWindowTitle(title);

    AddHandshakeTcpSettingsPanel();
    AddNoHandshakeTcpSettingsPanel();
    AddSSLTcpSettingsPanel();
}


/**
 *
 */
CMainWindow::~CMainWindow()
{
}


/**
 *
 */
void CMainWindow::OnNewTracesWindow()
{
    CTracesWindow*  pWnd = new CTracesWindow(NULL);
    pWnd->show();
}


/**
 *
 */
void CMainWindow::OnChannelsMgnt()
{
    QPoint              pt( m_pBtn_Channels->frameGeometry().left(), m_pBtn_Channels->frameGeometry().bottom() );

    pt = mapToGlobal(pt);

    CChannelsMgnt::Show(this, pt);
}


/**
 *
 */
void CMainWindow::OnAbout()
{
    CAboutDlg       dlg(this);

    dlg.exec();
}


/**
 * @brief CMainWindow::AddHandshakeTcpSettingsPanel
 */
void CMainWindow::AddHandshakeTcpSettingsPanel()
{
    m_pTcpIpSettingsPanel = new CTcpIpSettingsPanel();
    m_pTcpIpSettingsPanel->SetTracesReceiversSvr( &TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr(0) );
    ui->WithHandshakeGrpLayout->addWidget(m_pTcpIpSettingsPanel);

    QSize panelSize = m_pTcpIpSettingsPanel->size();
    QSize grpSize = ui->TcpWithHandshake->size();
    ui->TcpWithHandshake->setMinimumSize( panelSize.width(), panelSize.height() + grpSize.height() );
}


/**
 * @brief CMainWindow::AddNoHandshakeTcpSettingsPanel
 */
void CMainWindow::AddNoHandshakeTcpSettingsPanel()
{
    m_pTcpIpSettingsPanel = new CTcpIpSettingsPanel();
    m_pTcpIpSettingsPanel->SetTracesReceiversSvr( &TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr(1) );
    ui->WithoutHandshakeGrpLayout->addWidget(m_pTcpIpSettingsPanel);

    QSize panelSize = m_pTcpIpSettingsPanel->size();
    QSize grpSize = ui->TcpWithoutHandshake->size();
    ui->TcpWithoutHandshake->setMinimumSize( panelSize.width(), panelSize.height() + grpSize.height() );
}


/**
 * @brief CMainWindow::AddSSLTcpSettingsPanel
 */
void CMainWindow::AddSSLTcpSettingsPanel()
{
    m_pTcpIpSettingsPanel = new CTcpIpSettingsPanel();
    m_pTcpIpSettingsPanel->SetTracesReceiversSvr( &TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr(2) );
    ui->WithSSLGrpLayout->addWidget(m_pTcpIpSettingsPanel);

    QSize panelSize = m_pTcpIpSettingsPanel->size();
    QSize grpSize = ui->TcpSSL->size();
    ui->TcpSSL->setMinimumSize( panelSize.width(), panelSize.height() + grpSize.height() );
}


/**
 *
 */
void CMainWindow::closeEvent(QCloseEvent* pEvent)
{
    if ( CWindowsManager::Instance().TracesWindows().Count() > 0 )
    {
        hide();
        pEvent->ignore();
    }
}


/**
 *
 */
void CMainWindow::showEvent(QShowEvent *)
{
    CWindowsManager::Instance().OnShowWindow(this);
}


/**
 *
 */
void CMainWindow::hideEvent(QHideEvent *)
{
    CWindowsManager::Instance().OnHideWindow(this);
}
