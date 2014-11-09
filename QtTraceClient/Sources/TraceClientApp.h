#ifndef _TRACECLIENTAPP_HPP_
#define _TRACECLIENTAPP_HPP_

#include "AppSettings.hpp"
#include "WindowsManager.hpp"
#include "DevicesMapping.h"
#include "Servers/TextInputServer.h"

class CMainWindow;
class CTracesWindow;
class QApplication;
class CSettingsPanel;
class CDevicesSelectionPanel;
class QWidget;
class CTraceServerPortal;
class CDevicesMgr;
class CTraceServerMonitor;
class CTracesGroupViewMgr;


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

    const CAppSettings&     AppSettings() const         { return m_AppSettings; }
    CAppSettings&           AppSettings()               { return m_AppSettings; }

    CMainWindow*            MainWindow() const          { return m_pMainWindow; }

    CWindowsManager&        WindowsManager()            { return m_WindowsManager; }
    const CWindowsManager&  WindowsManager() const      { return m_WindowsManager; }

    const CDevicesMgr&      DevicesMgr() const          { return *m_pDevicesMgr; }
    CDevicesMgr&            DevicesMgr()                { return *m_pDevicesMgr; }

    const CDevicesMapping&  devicesMapping() const          { return m_DevicesMapping; }
    CDevicesMapping& devicesMapping()                       { return m_DevicesMapping; }

    void ShowSettings(QWidget* parent, const QPoint& pt = QPoint(0,0));
    void HideSettings();

    void ShowDevicesSelection(QWidget* parent, const QPoint& pt = QPoint(0,0));
    void HideDevicesSelection();

    CTraceServerPortal&     TraceServerPortal() const   { return *m_pTraceServerPortal; }
    CTraceServerMonitor&    TraceServerMonitor() const  { return *m_pTraceServerMonitor; }

    CTracesGroupViewMgr&    TracesGroupViewMgr() const  { return *m_pTracesGroupViewMgr; }

    const char* GetVersion() const;

public: // ITracesWindowsListener methods

    virtual void OnTracesWindows_Empty();

public slots:

    void onSettingsPanelClosed();
    virtual void onDevicesSelectionPanelClosed();

signals:

    void settingsPanelClosed();
    void devicesSelectionPanelClosed();

protected:

    void initDefaultSettings();
    void InitDefaultDrawSettings();



protected:

    QApplication*       m_pQtApplication;
    int                 m_AppReturnValue;
    CAppSettings        m_AppSettings;

    CWindowsManager     m_WindowsManager;

    CMainWindow*        m_pMainWindow;
    CTracesWindow*      m_pTracesWindow;

    CSettingsPanel*             m_pSettingsPanel;
    CDevicesSelectionPanel*     m_pDevicesSelectionPanel;
    CTraceServerPortal*         m_pTraceServerPortal;
    CTraceServerMonitor*        m_pTraceServerMonitor;

    CDevicesMgr*                m_pDevicesMgr;
    CDevicesMapping             m_DevicesMapping;
    CTracesGroupViewMgr*        m_pTracesGroupViewMgr;

    CTextInputServer            _textInputServer;

    static CTraceClientApp*     s_pInstance;
};


#endif // _TRACECLIENTAPP_HPP_
