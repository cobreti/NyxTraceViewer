#ifndef _TRACECLIENTAPP_HPP_
#define _TRACECLIENTAPP_HPP_

#include <QtGui>

#include "AppSettings.hpp"
#include "TracesWindows.hpp"

class CMainWindow;
class CTracesWindow;
class QApplication;

class CTraceClientApp : public QObject,
                        public ITracesWindowsListener
{
    Q_OBJECT

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

    const CTracesWindows&   TracesWindows() const       { return m_TracesWindows; }
    CTracesWindows&         TracesWindows()             { return m_TracesWindows; }

    const char* GetVersion() const;

public: // ITracesWindowsListener methods

    virtual void OnTracesWindows_Empty();

public slots:

signals:

protected:

    void initDefaultSettings();
    void InitDefaultDrawSettings();

protected:

    QApplication*       m_pQtApplication;
    CMainWindow*        m_pMainWindow;
    int                 m_AppReturnValue;
    CAppSettings        m_AppSettings;

    CTracesWindow*      m_pTracesWindow;
    CTracesWindows      m_TracesWindows;

    static CTraceClientApp*     s_pInstance;
};


#endif // _TRACECLIENTAPP_HPP_
