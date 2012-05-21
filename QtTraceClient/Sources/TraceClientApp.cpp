#include <QtGui>
#include <QtGui/QApplication>

#include "TraceClientApp.h"

#include <Nyx.hpp>

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
    m_pTracesWindow(NULL)
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
    m_TracesWindows.SetListener( static_cast<ITracesWindowsListener*>(this) );

    m_pQtApplication = new QApplication(argc, argv);

    initDefaultSettings();

    m_pTracesWindow = new CTracesWindow(NULL);
    m_pTracesWindow->show();

    TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceivers().Start();
}


/**
 *
 */
void CTraceClientApp::Run()
{
    TraceClientCore::CModule::Instance().PoolsUpdateClock().Start();

    m_AppReturnValue = m_pQtApplication->exec();
}


/**
 *
 */
void CTraceClientApp::Destroy()
{
    delete m_pQtApplication;
    m_pQtApplication = NULL;

    TraceClientCore::CModule::Instance().PoolsUpdateClock().Stop();
    TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceivers().Stop();
    TraceClientCore::CModule::Instance().TraceChannels().Stop();
}


/**
 *
 */
const char* CTraceClientApp::GetVersion() const
{
    return "0.0.0.2";
}


/**
 *
 */
void CTraceClientApp::OnTracesWindows_Empty()
{
    m_pQtApplication->quit();
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


