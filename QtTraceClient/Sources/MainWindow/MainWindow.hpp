#ifndef _MAINWINDOW_HPP_
#define _MAINWINDOW_HPP_

#include <QMainWindow>

class QToolButton;


namespace Ui
{
    class MainWindow;
}

class CReceiversListenerBridge;

/**
 * @brief The CMainWindow class
 */
class CMainWindow : public QMainWindow
{
    Q_OBJECT

    friend class CReceiversListenerBridge;

public:
    CMainWindow();
    virtual ~CMainWindow();

public slots:

    void OnNewTracesWindow();
    void OnChannelsMgnt();
    void OnAbout();
    void OnStartStopReceivers();

protected:

    virtual void closeEvent(QCloseEvent *);
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

    void UpdateTcpIpStartStopButton();

protected:

    Ui::MainWindow*     ui;

    QToolButton*        m_pBtn_NewView;
    QToolButton*        m_pBtn_Channels;
    QToolButton*        m_pBtn_About;

    CReceiversListenerBridge*    m_pReceiversListenerBridge;
};




#endif // _MAINWINDOW_HPP_
