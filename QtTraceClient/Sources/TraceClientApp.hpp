#ifndef _TRACECLIENTAPP_HPP_
#define _TRACECLIENTAPP_HPP_

class CMainWindow;
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
    CMainWindow* MainWindow() const         { return m_pMainWindow; }

protected:

    QApplication*       m_pQtApplication;
    CMainWindow*        m_pMainWindow;
    int                 m_AppReturnValue;

    static CTraceClientApp*     s_pInstance;
};


#endif // _TRACECLIENTAPP_HPP_
