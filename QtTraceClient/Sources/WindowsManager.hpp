#ifndef WINDOWSMANAGER_HPP_
#define WINDOWSMANAGER_HPP_

#include "TracesWindows.hpp"

#include <QMainWindow>

class CMainWindow;

/**
 * @brief The CWindowsManager class
 */
class CWindowsManager
{
public:

    static CWindowsManager& Instance();

public:
    CWindowsManager();
    virtual ~CWindowsManager();

    virtual void Init();
    virtual void Terminate();

    const CTracesWindows&   TracesWindows() const       { return m_TracesWindows; }
    CTracesWindows&         TracesWindows()             { return m_TracesWindows; }

    void OnShowWindow( CMainWindow* pWindow );
    void OnShowWindow( CTracesWindow* pWindow );

    void OnHideWindow( CMainWindow* pWindow );
    void OnHideWindow( CTracesWindow* pWindow );

    void OnWindowClosing( CTracesWindow* pWindow );

    void OnWindowMoved( CTracesWindow* pWindow, const QPoint& newPos );

    void AddTracesWindow( CTracesWindow* pWnd );
    void RemoveTracesWindow( CTracesWindow* pWnd );

protected:

    /**
     * @brief The XTopLevelWndInfo class
     */
    class XTopLevelWndInfo
    {
    public:
        XTopLevelWndInfo() : m_pWnd(NULL) {}
        XTopLevelWndInfo( CTracesWindow* pWnd, const QPoint& pos ) :
            m_pWnd(pWnd), m_WndPos(pos) {}
        XTopLevelWndInfo(const XTopLevelWndInfo& info) :
            m_pWnd(info.m_pWnd), m_WndPos(info.m_WndPos) {}
        ~XTopLevelWndInfo() {}

        CTracesWindow*  Window() const      { return m_pWnd; }
        CTracesWindow*& Window()            { return m_pWnd; }

        const QPoint&   WindowPos() const   { return m_WndPos; }
        QPoint&         WindowPos()         { return m_WndPos; }

        const XTopLevelWndInfo& operator = (const XTopLevelWndInfo& info)
        {
            m_pWnd = info.m_pWnd;
            m_WndPos = info.m_WndPos;
            return *this;
        }

        bool Valid() const      { return m_pWnd != NULL; }
        void Clear()            { m_pWnd = NULL; m_WndPos = QPoint(); }

    protected:

        CTracesWindow*      m_pWnd;
        QPoint              m_WndPos;
    };

protected:

    CTracesWindows      m_TracesWindows;
    QMainWindow*        m_pDummyParentWindow;

    XTopLevelWndInfo    m_CurrentTopLevel;
    XTopLevelWndInfo    m_LastTopLevel;
};

#endif // WINDOWSMANAGER_HPP_
