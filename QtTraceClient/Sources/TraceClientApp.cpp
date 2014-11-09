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
#include "ServerAccess/TraceServerMonitor.h"
#include "DevicesMgr.h"
#include "Config/ConfigReader.hpp"
#include "View/TracesGroupViewMgr.h"

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
    m_pTraceServerMonitor(NULL),
    m_pDevicesMgr(),
    m_pTracesGroupViewMgr(NULL)
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

    QRect           rcScreen = m_pQtApplication->desktop()->availableGeometry();

    QString path = m_pQtApplication->applicationDirPath();
    std::string strPath = path.toStdString();

    NYXTRACE(0x0, L"current path : " << Nyx::CTF_AnsiText(strPath.c_str()) );

    Nyx::CAString      certificateFile( strPath.c_str() );
    certificateFile += "/SSL/certificate.pem";

    Nyx::CAString       privKeyFile( strPath.c_str() );
    privKeyFile += "/SSL/privkey.pem";

    Nyx::CAString       bioFile( strPath.c_str() );
    bioFile += "/SSL/dh1024.pem";

    int     basePortNumber = 8500;

    TraceClientCore::CTcpTracesReceiversSvr::CSettings     settings;
    settings.PortNumber() = basePortNumber;
    settings.UseHandshake() = true;
    TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr(0).Start(settings);

//    _textInputServer.Start();

    settings.PortNumber() = basePortNumber + 1;
    settings.UseHandshake() = false;
    TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr(1).Start(settings);

    settings.PortNumber() = basePortNumber + 2;
    settings.UseHandshake() = false;
    settings.UseSSL() = true;
    settings.CertificateFile() = certificateFile;
    settings.PrivKeyFile() = privKeyFile;
    settings.DhFile() = bioFile;
    TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr(2).Start(settings);

    m_pMainWindow = new CMainWindow();
    m_pMainWindow->move( rcScreen.left(), rcScreen.top() );

    m_pTracesWindow = new CTracesWindow(NULL);
    m_pTracesWindow->setParent(NULL, Qt::Window);

    m_pSettingsPanel = new CSettingsPanel();
    m_pDevicesSelectionPanel = new CDevicesSelectionPanel();
    m_pTraceServerPortal = new CTraceServerPortal();
    m_pTraceServerMonitor = new CTraceServerMonitor(*m_pTraceServerPortal);
    m_pDevicesMgr = new CDevicesMgr();
    m_pTracesGroupViewMgr = new CTracesGroupViewMgr();

    connect(    m_pSettingsPanel, SIGNAL(closing()),
                this, SLOT(onSettingsPanelClosed()) );
    connect(    m_pDevicesSelectionPanel, SIGNAL(closing()),
                this, SLOT(onDevicesSelectionPanelClosed()) );

    CConfigReader       configReader;

    configReader.Load();

    m_pTracesWindow->show();

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

    delete m_pTracesGroupViewMgr;
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
//    return " - in development";
    return "1.0.8x";
}


/**
 *
 */
void CTraceClientApp::OnTracesWindows_Empty()
{
}



/**
 * @brief CTraceClientApp::onSettingsPanelClosed
 */
void CTraceClientApp::onSettingsPanelClosed()
{
    emit settingsPanelClosed();
}


/**
 * @brief CTraceClientApp::onDevicesSelectionPanelClosed
 */
void CTraceClientApp::onDevicesSelectionPanelClosed()
{
    emit devicesSelectionPanelClosed();
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


