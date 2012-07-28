#ifndef WINDOWSMANAGER_HPP_
#define WINDOWSMANAGER_HPP_

#include "TracesWindows.hpp"

#include <QMainWindow>

class CMainWindow;

/**
 *
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

    void AddTracesWindow( CTracesWindow* pWnd );
    void RemoveTracesWindow( CTracesWindow* pWnd );

protected:

    CTracesWindows      m_TracesWindows;
    QMainWindow*        m_pDummyParentWindow;

    struct
    {
        CTracesWindow*      pWindow;
        QPoint              pos;
    }                   m_LastTopLevel;
};

#endif // WINDOWSMANAGER_HPP_
