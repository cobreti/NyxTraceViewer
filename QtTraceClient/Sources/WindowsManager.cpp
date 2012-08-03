#include "WindowsManager.hpp"
#include "TraceClientApp.h"
#include "TracesWindow.hpp"
#include "TracesWindows.hpp"
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
//    if ( m_CurrentTopLevel.Valid() )
//    {
////        m_CurrentTopLevel.Window()->setParent(m_pDummyParentWindow, Qt::Window);
//        m_CurrentTopLevel.Window()->showNormal();
//        m_CurrentTopLevel.Window()->move( m_CurrentTopLevel.WindowPos() );

//        m_LastTopLevel = m_CurrentTopLevel;
//        m_CurrentTopLevel.Clear();
//    }
}


/**
 * @brief CWindowsManager::OnShowWindow
 * @param pWindow
 */
void CWindowsManager::OnShowWindow(CTracesWindow *pWindow)
{
//    if ( pWindow->isMinimized() )
//    {
//        return;
//    }

//    CMainWindow*        pMainWindow = CTraceClientApp::Instance().MainWindow();

//    if ( !m_CurrentTopLevel.Valid() && pMainWindow->isHidden() )
//    {
//        m_CurrentTopLevel = XTopLevelWndInfo(pWindow, pWindow->pos());
//    }
}


/**
 *
 */
void CWindowsManager::OnHideWindow(CMainWindow *pWindow)
{
//    if ( pWindow->isMinimized() )
//    {
//        return;
//    }

//    QApplication*   pApp = qobject_cast<QApplication*>(QApplication::instance());
//    QWidget*        pActiveWindow = pApp->activeWindow();
//    CTracesWindow*  pTracesWindow = TracesWindows().FindRelatedTracesWindow(pActiveWindow);

//    if ( pTracesWindow == NULL )
//        pTracesWindow = TracesWindows().GetTopWindow();

//    if ( pTracesWindow != NULL )
//    {
//        m_CurrentTopLevel = XTopLevelWndInfo(pTracesWindow, pTracesWindow->pos());
////        m_CurrentTopLevel.Window()->setParent(NULL, Qt::Window);
//        m_CurrentTopLevel.Window()->showNormal();
//        m_CurrentTopLevel.Window()->move( m_CurrentTopLevel.WindowPos() );
//    }
//    else
//        m_CurrentTopLevel.Clear();
}


/**
 *
 */
void CWindowsManager::OnHideWindow(CTracesWindow *pWindow)
{
//    if ( pWindow->isMinimized() )
//    {
////        if ( pWindow != m_CurrentTopLevel.Window() )
////            pWindow->setParent(NULL, Qt::Window);

//        return;
//    }

//    QApplication*   pApp = qobject_cast<QApplication*>(QApplication::instance());
//    QWidget*        pMainWindow = CTraceClientApp::Instance().MainWindow();

//    if ( m_CurrentTopLevel.Valid() && m_CurrentTopLevel.Window() == pWindow )
//    {
//        CTracesWindow* pTracesWindow = TracesWindows().GetTopWindow();

//        if ( pTracesWindow != NULL )
//        {
//            m_CurrentTopLevel = XTopLevelWndInfo(pTracesWindow, pTracesWindow->pos());
////            m_CurrentTopLevel.Window()->setParent(NULL, Qt::Window);
//            m_CurrentTopLevel.Window()->showNormal();
//            m_CurrentTopLevel.Window()->move( m_CurrentTopLevel.WindowPos() );
//        }
//        else
//            m_CurrentTopLevel.Clear();

//    }
}


/**
 *
 */
void CWindowsManager::OnWindowClosing(CTracesWindow *pWindow)
{
    RemoveTracesWindow(pWindow);

    if ( pWindow == m_CurrentTopLevel.Window() )
    {
        m_CurrentTopLevel.Clear();

        if ( TracesWindows().Count() > 0 )
        {
//            CTracesWindow* pWnd = TracesWindows().GetTopWindow();

//            m_CurrentTopLevel = XTopLevelWndInfo(pWnd, pWnd->pos());

////            m_CurrentTopLevel.Window()->setParent(NULL, Qt::Window);
//            m_CurrentTopLevel.Window()->showNormal();
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
void CWindowsManager::OnWindowMoved( CTracesWindow* pWindow, const QPoint& newPos )
{
    if ( pWindow == m_CurrentTopLevel.Window() )
        m_CurrentTopLevel.WindowPos() = newPos;
}


/**
 *
 */
void CWindowsManager::AddTracesWindow(CTracesWindow *pWnd)
{
    TracesWindows().Insert(pWnd);

//    pWnd->setParent( m_pDummyParentWindow, Qt::Window );
}


/**
 *
 */
void CWindowsManager::RemoveTracesWindow(CTracesWindow *pWnd)
{
    TracesWindows().Remove(pWnd);
}
