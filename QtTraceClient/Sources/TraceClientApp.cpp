#include <QtGui>
#include <QApplication>
#include <QDesktopWidget>

#include "TraceClientApp.h"

#include <Nyx.hpp>

#include "MainWindow/MainWindow.hpp"
#include "TracesWindow.hpp"
#include "Panels/SettingsPanel.h"
#include "Panels/DevicesSelectionPanel.h"
#include "PoolsUpdateClock.hpp"
#include "ServerAccess/TraceServerPortal.h"
#include "DevicesMgr.h"

#include "TraceClientCoreModule.hpp"

#include <QWidget>
#include <QLayout>


/**
 *
 */
CTraceClientApp* CTraceClientApp::s_pInstance = NULL;


/**
 *
 */
CTraceClientApp& CTraceClientApp::Instance()
{
    return *s_pInstance;
}


/**
 *
 */
CTraceClientApp::CTraceClientApp() : QObject(),
    m_pQtApplication(NULL),
    m_AppReturnValue(-1),
    m_pTracesWindow(NULL),
    m_pMainWindow(NULL),
    m_pSettingsPanel(NULL),
    m_pDevicesSelectionPanel(NULL),
    m_pTraceServerPortal(NULL),
    m_pDevicesMgr()
{
    s_pInstance = this;
}


/**
 *
 */
CTraceClientApp::~CTraceClientApp()
{
    s_pInstance = NULL;
}


/**
 *
 */
void CTraceClientApp::Init(int &argc, char **argv)
{
    WindowsManager().TracesWindows().SetListener( static_cast<ITracesWindowsListener*>(this) );

    m_pQtApplication = new QApplication(argc, argv);

    WindowsManager().Init();

    initDefaultSettings();

    QApplication*   pApp = qobject_cast<QApplication*>(QApplication::instance());
    QRect           rcScreen = pApp->desktop()->availableGeometry();

    QString path = pApp->applicationDirPath();
    std::string strPath = path.toStdString();

    NYXTRACE(0x0, L"current path : " << Nyx::CTF_AnsiText(strPath.c_str()) );

    Nyx::CAString      certificateFile( strPath.c_str() );
    certificateFile += "/SSL/certificate.pem";

    Nyx::CAString       privKeyFile( strPath.c_str() );
    privKeyFile += "/SSL/privkey.pem";

    Nyx::CAString       bioFile( strPath.c_str() );
    bioFile += "/SSL/dh1024.pem";

    TraceClientCore::CTcpTracesReceiversSvr::CSettings     settings;
    settings.PortNumber() = 8500;
    settings.UseHandshake() = true;
    TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr(0).Start(settings);

    settings.PortNumber() = 8501;
    settings.UseHandshake() = false;
    TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr(1).Start(settings);

    settings.PortNumber() = 8502;
    settings.UseHandshake() = false;
    settings.UseSSL() = true;
    settings.CertificateFile() = certificateFile;
    settings.PrivKeyFile() = privKeyFile;
    settings.DhFile() = bioFile;
    TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr(2).Start(settings);

    m_pMainWindow = new CMainWindow();
    m_pMainWindow->move( rcScreen.left(), rcScreen.top() );
//    m_pMainWindow->show();

    m_pTracesWindow = new CTracesWindow(NULL);
    m_pTracesWindow->setParent(NULL, Qt::Window);
    m_pTracesWindow->show();

    m_pSettingsPanel = new CSettingsPanel();
    m_pDevicesSelectionPanel = new CDevicesSelectionPanel();
    m_pTraceServerPortal = new CTraceServerPortal();
    m_pDevicesMgr = new CDevicesMgr();

    connect(    &m_serverHeartbeatTimer, SIGNAL(timeout()),
                this, SLOT(onServerHeartbeatTimerTimeout()) );

    devicesMapping().Init();
}


/**
 *
 */
void CTraceClientApp::Run()
{
    TraceClientCore::CModule::Instance().PoolsUpdateClock().Start();

    m_AppReturnValue = m_pQtApplication->exec();

    TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr(0).Listeners()->Clear();
}


/**
 *
 */
void CTraceClientApp::Destroy()
{
    delete m_pQtApplication;
    m_pQtApplication = NULL;

    TraceClientCore::CModule::Instance().PoolsUpdateClock().Stop();
    TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr(0).Stop();
    TraceClientCore::CModule::Instance().TraceChannels().Stop();

    WindowsManager().Terminate();
}


void CTraceClientApp::ShowSettings(QWidget *parent, const QPoint& pt )
{
    m_pSettingsPanel->setParent(parent);
    m_pSettingsPanel->show();
    m_pSettingsPanel->move(pt);
    m_pSettingsPanel->raise();
}


void CTraceClientApp::HideSettings()
{
    m_pSettingsPanel->hide();
    m_pSettingsPanel->setParent(NULL);
}


void CTraceClientApp::ShowDevicesSelection(QWidget *parent, const QPoint &pt)
{
    m_pDevicesSelectionPanel->setParent(parent);
    m_pDevicesSelectionPanel->show();
    m_pDevicesSelectionPanel->move(pt);
    m_pDevicesSelectionPanel->raise();
}


void CTraceClientApp::HideDevicesSelection()
{
    m_pDevicesSelectionPanel->hide();
    m_pDevicesSelectionPanel->setParent(NULL);
}


/**
 *
 */
const char* CTraceClientApp::GetVersion() const
{
    return "1.0.1";
}


/**
 *
 */
void CTraceClientApp::startServerConnectionMonitor()
{
    connect(    m_pTraceServerPortal, SIGNAL(heartbeatSuccessfull()),
                this, SLOT(onServerHeartbeatSuccessfull()) );
    connect(    m_pTraceServerPortal, SIGNAL(heartbeatFailure()),
                this, SLOT(onServerHeartbeatFailure()) );


    m_serverHeartbeatTimer.setSingleShot(true);
    m_serverHeartbeatTimer.setInterval(5000);

    m_pTraceServerPortal->checkServerConnection();
}


/**
 *
 */
void CTraceClientApp::OnTracesWindows_Empty()
{
    //m_pQtApplication->quit();
}


/**
 * @brief CTraceClientApp::onServerHeartbeatSuccessfull
 */
void CTraceClientApp::onServerHeartbeatSuccessfull()
{
    NYXTRACE(0x0, L"onServerHeartbeatSuccessfull");

    emit serverHeartbeatSuccess();

    m_serverHeartbeatTimer.start();
}


/**
 * @brief CTraceClientApp::onServerHeartbeatFailure
 */
void CTraceClientApp::onServerHeartbeatFailure()
{
    NYXTRACE(0x0, L"onServerHeartbeatFailure");

    disconnect( m_pTraceServerPortal, SIGNAL(heartbeatSuccessfull()),
                this, SLOT(onServerHeartbeatSuccessfull()) );
    disconnect( m_pTraceServerPortal, SIGNAL(heartbeatFailure()),
                this, SLOT(onServerHeartbeatFailure()) );

    emit serverHeartbeatFailure();
}



void CTraceClientApp::onServerHeartbeatTimerTimeout()
{
    m_serverHeartbeatTimer.setSingleShot(true);

    m_pTraceServerPortal->checkServerConnection();
}


/**
 *
 */
void CTraceClientApp::initDefaultSettings()
{
    InitDefaultDrawSettings();
}


/**
 *
 */
void CTraceClientApp::InitDefaultDrawSettings()
{
    CViewDrawSettings&      rDrawSettings = m_AppSettings.DefaultDrawSettings();

//    rDrawSettings.Painter( CViewItemPainter::ePId_Row ) = new CViewItemBackgroundPainter();
//    rDrawSettings.Painter( CViewItemPainter::ePId_LineNumber ) = new CViewItemLineNumberPainter();
//    rDrawSettings.Painter( CViewItemPainter::ePId_ModuleName ) = new CViewItemModuleNamePainter();
//    rDrawSettings.Painter( CViewItemPainter::ePId_TickCount ) = new CViewItemTickCountPainter();
//    rDrawSettings.Painter( CViewItemPainter::ePId_ThreadId ) = new CViewItemThreadIdPainter();
//    rDrawSettings.Painter( CViewItemPainter::ePId_Data ) = new CViewItemDataPainter();
    rDrawSettings.CalculateLineHeight();
}


