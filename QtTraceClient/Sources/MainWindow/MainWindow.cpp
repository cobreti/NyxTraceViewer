#include "MainWindow.hpp"
#include "TracesWindow.hpp"
#include "ChannelsMgnt/ChannelsMgnt.hpp"
#include "Dialogs/AboutDlg.h"
#include "TraceClientApp.h"
#include "TraceClientCoreModule.hpp"


#include <QToolButton>
#include <QCloseEvent>

#include "ui_MainWindow.h"


class CReceiversListenerBridge : public Nyx::CObject_Impl<TraceClientCore::ITcpTracesReceiversListener>
{
public:
    CReceiversListenerBridge( CMainWindow& rMainWindow ) :
        m_rMainWindow(rMainWindow)
    {
    }

    ~CReceiversListenerBridge()
    {
    }

    virtual void OnReceiversStarted()
    {
        m_rMainWindow.UpdateTcpIpStartStopButton();
    }

    virtual void OnReceiversStopped()
    {
        m_rMainWindow.UpdateTcpIpStartStopButton();
    }

protected:

    CMainWindow&                                m_rMainWindow;
};



/**
 *
 */
CMainWindow::CMainWindow() : QMainWindow(),
    ui( new Ui::MainWindow()),
    m_pBtn_NewView(NULL),
    m_pBtn_Channels(NULL),
    m_pBtn_About(NULL),
    m_pReceiversListenerBridge(NULL)
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
    connect( ui->m_btnStartStop, SIGNAL(clicked()), this, SLOT(OnStartStopReceivers()));

    QString     title = windowTitle();
    title += "     v";
    title += CTraceClientApp::Instance().GetVersion();
    setWindowTitle(title);

    TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceivers().Listeners()->Add( new CReceiversListenerBridge(*this) );
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
 *
 */
void CMainWindow::OnStartStopReceivers()
{
    TraceClientCore::CTcpTracesReceivers&   rTracesReceivers = TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceivers();

    ui->m_btnStartStop->setEnabled(false);

    if ( rTracesReceivers.IsRunning() )
        rTracesReceivers.Stop();
    else
        rTracesReceivers.Start();

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

    UpdateTcpIpStartStopButton();
//    QApplication*       pApp = static_cast<QApplication*>(QApplication::instance());
//    QWidget*            pActiveWnd = pApp->activeWindow();

//    NYXTRACE(0x0, L"main window show event : " << Nyx::CTF_Ptr(this) << L" / active window : " << Nyx::CTF_Ptr(pActiveWnd) );
}


/**
 *
 */
void CMainWindow::hideEvent(QHideEvent *)
{
    CWindowsManager::Instance().OnHideWindow(this);

//    QApplication*       pApp = static_cast<QApplication*>(QApplication::instance());
//    QWidget*            pActiveWnd = pApp->activeWindow();

//    NYXTRACE(0x0, L"main window hide event : " << Nyx::CTF_Ptr(this) << L" / active window : " << Nyx::CTF_Ptr(pActiveWnd) );
}


/**
 *
 */
void CMainWindow::UpdateTcpIpStartStopButton()
{
    QIcon               StopIcon(":/MainWindow/Stop");
    QIcon               StartIcon(":/MainWindow/Start");

    if ( TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceivers().IsRunning() )
        ui->m_btnStartStop->setIcon(StopIcon);
    else
        ui->m_btnStartStop->setIcon(StartIcon);

    ui->m_btnStartStop->setEnabled(true);
}
