#include "WindowsManager.hpp"
#include "TraceClientApp.h"
#include "TracesWindow.hpp"
#include "MainWindow/MainWindow.hpp"

#include <QApplication>

/**
 *
 */
CWindowsManager& CWindowsManager::Instance()
{
    return CTraceClientApp::Instance().WindowsManager();
}


/**
 *
 */
CWindowsManager::CWindowsManager() :
    m_pDummyParentWindow(NULL)
{
    m_LastTopLevel.pWindow = NULL;
}


/**
 *
 */
CWindowsManager::~CWindowsManager()
{
}


/**
 *
 */
void CWindowsManager::Init()
{
    m_pDummyParentWindow = new QMainWindow();
}


/**
 *
 */
void CWindowsManager::Terminate()
{
    delete m_pDummyParentWindow;
    m_pDummyParentWindow = NULL;
}


/**
 *
 */
void CWindowsManager::OnShowWindow(CMainWindow *pWindow)
{
    if ( m_LastTopLevel.pWindow != NULL )
    {
        m_LastTopLevel.pWindow->setParent(m_pDummyParentWindow, Qt::Window);
        m_LastTopLevel.pWindow->show();
        m_LastTopLevel.pWindow->move( m_LastTopLevel.pos );
    }
}


/**
 *
 */
void CWindowsManager::OnShowWindow(CTracesWindow *pWindow)
{
    CMainWindow*        pMainWindow = CTraceClientApp::Instance().MainWindow();

    if ( m_LastTopLevel.pWindow == NULL && pMainWindow->isHidden() )
    {
        m_LastTopLevel.pWindow = pWindow;
        m_LastTopLevel.pos = pWindow->pos();
    }
}


/**
 *
 */
void CWindowsManager::OnHideWindow(CMainWindow *pWindow)
{
    QApplication*   pApp = qobject_cast<QApplication*>(QApplication::instance());
    QWidget*        pActiveWindow = pApp->activeWindow();
    CTracesWindow*  pTracesWindow = TracesWindows().FindRelatedTracesWindow(pActiveWindow);

    if ( pTracesWindow == NULL )
        pTracesWindow = TracesWindows().GetTopWindow();

    m_LastTopLevel.pWindow = pTracesWindow;

    if ( pTracesWindow != NULL )
    {
        m_LastTopLevel.pos = pTracesWindow->pos();
        pTracesWindow->setParent(NULL, Qt::Window);
        pTracesWindow->show();
        pTracesWindow->move( m_LastTopLevel.pos );
    }
}


/**
 *
 */
void CWindowsManager::OnHideWindow(CTracesWindow *pWindow)
{
    QApplication*   pApp = qobject_cast<QApplication*>(QApplication::instance());
    QWidget*        pMainWindow = CTraceClientApp::Instance().MainWindow();

    if ( pWindow == m_LastTopLevel.pWindow && pMainWindow->isHidden() )
    {
         CTracesWindow* pTracesWindow = TracesWindows().GetTopWindow();

        m_LastTopLevel.pWindow = pTracesWindow;

        if ( pTracesWindow != NULL )
        {
            m_LastTopLevel.pos = pTracesWindow->pos();
            pTracesWindow->setParent(NULL, Qt::Window);
            pTracesWindow->show();
            pTracesWindow->move( m_LastTopLevel.pos );
        }
    }
}


/**
 *
 */
void CWindowsManager::OnWindowClosing(CTracesWindow *pWindow)
{
    RemoveTracesWindow(pWindow);

    if ( pWindow == m_LastTopLevel.pWindow )
    {
        m_LastTopLevel.pWindow = NULL;

        if ( TracesWindows().Count() > 0 )
        {
            m_LastTopLevel.pWindow = TracesWindows().GetTopWindow();
            m_LastTopLevel.pos = m_LastTopLevel.pWindow->pos();
            m_LastTopLevel.pWindow->setParent(NULL, Qt::Window);
            m_LastTopLevel.pWindow->show();
        }
        else
        {
            CTraceClientApp::Instance().MainWindow()->show();
        }
    }
}


/**
 *
 */
void CWindowsManager::AddTracesWindow(CTracesWindow *pWnd)
{
    TracesWindows().Insert(pWnd);

    pWnd->setParent( m_pDummyParentWindow, Qt::Window );
}


/**
 *
 */
void CWindowsManager::RemoveTracesWindow(CTracesWindow *pWnd)
{
    TracesWindows().Remove(pWnd);
}
