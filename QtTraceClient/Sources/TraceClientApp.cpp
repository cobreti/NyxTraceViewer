#include <QtGui>
#include <QtGui/QApplication>

#include "TraceClientApp.h"

#include <Nyx.hpp>

#include "MainWindow/MainWindow.hpp"
#include "TracesWindow.hpp"
#include "View/ViewItemBackgroundPainter.hpp"
#include "View/ViewItemModuleNamePainter.hpp"
#include "View/ViewItemTickCountPainter.hpp"
#include "View/ViewItemThreadIdPainter.hpp"
#include "View/ViewItemDataPainter.hpp"
#include "View/ViewItemLineNumberPainter.hpp"
#include "PoolsUpdateClock.hpp"

#include "TraceClientCoreModule.hpp"

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
    m_pMainWindow(NULL)
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

    m_pMainWindow = new CMainWindow();
    m_pMainWindow->move( rcScreen.left(), rcScreen.top() );
//    m_pMainWindow->show();

    m_pTracesWindow = new CTracesWindow(NULL);
    m_pTracesWindow->setParent(NULL, Qt::Window);
    m_pTracesWindow->show();

    TraceClientCore::CTcpTracesReceiversSvr::CSettings     settings;
    settings.PortNumber() = 8500;
    settings.UseHandshake() = true;
    TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr(0).Start(settings);

    settings.PortNumber() = 8501;
    settings.UseHandshake() = false;
    TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr(1).Start(settings);
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


/**
 *
 */
const char* CTraceClientApp::GetVersion() const
{
    return "1.0.8x";
}


/**
 *
 */
void CTraceClientApp::OnTracesWindows_Empty()
{
    //m_pQtApplication->quit();
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

    rDrawSettings.Painter( CViewItemPainter::ePId_Row ) = new CViewItemBackgroundPainter();
    rDrawSettings.Painter( CViewItemPainter::ePId_LineNumber ) = new CViewItemLineNumberPainter();
    rDrawSettings.Painter( CViewItemPainter::ePId_ModuleName ) = new CViewItemModuleNamePainter();
    rDrawSettings.Painter( CViewItemPainter::ePId_TickCount ) = new CViewItemTickCountPainter();
    rDrawSettings.Painter( CViewItemPainter::ePId_ThreadId ) = new CViewItemThreadIdPainter();
    rDrawSettings.Painter( CViewItemPainter::ePId_Data ) = new CViewItemDataPainter();
    rDrawSettings.CalculateLineHeight();
}


