#ifndef _TRACECLIENTAPP_HPP_
#define _TRACECLIENTAPP_HPP_

#include "AppSettings.hpp"

class CMainWindow;
class CTracesWindow;
class QApplication;

class CTraceClientApp
{
public:
    static CTraceClientApp& Instance();

public:
    CTraceClientApp();
    ~CTraceClientApp();

    void Init(int &argc, char **argv);
    void Run();
    void Destroy();

    int ReturnValue() const                 { return m_AppReturnValue; }
    //CMainWindow* MainWindow() const         { return m_pMainWindow; }

    const CAppSettings&     AppSettings() const         { return m_AppSettings; }
    CAppSettings&           AppSettings()               { return m_AppSettings; }

    const char* GetVersion() const;

protected:

    void initDefaultSettings();
    void InitDefaultDrawSettings();

protected:

    QApplication*       m_pQtApplication;
    CMainWindow*        m_pMainWindow;
    int                 m_AppReturnValue;
    CAppSettings        m_AppSettings;

    CTracesWindow*      m_pTracesWindow;

    static CTraceClientApp*     s_pInstance;
};


#endif // _TRACECLIENTAPP_HPP_
