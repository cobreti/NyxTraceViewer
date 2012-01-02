#include <Nyx.hpp>
#include <QtGui>
#include <QtGui/QApplication>

#include "TraceClientApp.hpp"
#include "MainWindow.h"
#include "View/ViewItemBackgroundPainter.hpp"
#include "View/ViewItemModuleNamePainter.hpp"
#include "View/ViewItemTickCountPainter.hpp"
#include "View/ViewItemThreadIdPainter.hpp"
#include "View/ViewItemDataPainter.hpp"
#include "View/ViewItemLineNumberPainter.hpp"


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
CTraceClientApp::CTraceClientApp() :
    m_pQtApplication(NULL),
    m_pMainWindow(NULL),
    m_AppReturnValue(-1)
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
    m_pQtApplication = new QApplication(argc, argv);

    initDefaultSettings();

    m_pMainWindow = new CMainWindow;

    TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceivers().Start();
}


/**
 *
 */
void CTraceClientApp::Run()
{
    m_pMainWindow->show();
    m_AppReturnValue = m_pQtApplication->exec();
}


/**
 *
 */
void CTraceClientApp::Destroy()
{
    TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceivers().Stop();

    delete m_pMainWindow;
    m_pMainWindow = NULL;

    delete m_pQtApplication;
    m_pQtApplication = NULL;
}


/**
 *
 */
const char* CTraceClientApp::GetVersion() const
{
    return "0.0.0.1";
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


