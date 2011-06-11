#include <Nyx.hpp>
#include <QtGui>
#include <QtGui/QApplication>

#include "TraceClientApp.hpp"
#include "MainWindow.h"

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

    m_pMainWindow = new CMainWindow;
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
    delete m_pMainWindow;
    m_pMainWindow = NULL;

    delete m_pQtApplication;
    m_pQtApplication = NULL;
}
