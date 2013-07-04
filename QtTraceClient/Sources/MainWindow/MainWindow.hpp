#ifndef _MAINWINDOW_HPP_
#define _MAINWINDOW_HPP_

#include <QMainWindow>

class QToolButton;


namespace Ui
{
    class MainWindow;
}

class CTcpIpSettingsPanel;

/**
 * @brief The CMainWindow class
 */
class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CMainWindow();
    virtual ~CMainWindow();

public slots:

    void OnNewTracesWindow();
    void OnChannelsMgnt();
    void OnAbout();

protected:

    void AddHandshakeTcpSettingsPanel();
    void AddNoHandshakeTcpSettingsPanel();
    void AddSSLTcpSettingsPanel();

    virtual void closeEvent(QCloseEvent *);
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

protected:

    Ui::MainWindow*     ui;

    QToolButton*        m_pBtn_NewView;
    QToolButton*        m_pBtn_Channels;
    QToolButton*        m_pBtn_About;

    CTcpIpSettingsPanel*        m_pTcpIpSettingsPanel;
};




#endif // _MAINWINDOW_HPP_
