#ifndef _MAINWINDOW_HPP_
#define _MAINWINDOW_HPP_

#include <QMainWindow>


class QToolButton;


namespace Ui
{
    class MainWindow;
}


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

    Ui::MainWindow*     ui;

    QToolButton*        m_pBtn_NewView;
    QToolButton*        m_pBtn_Channels;
    QToolButton*        m_pBtn_About;
};




#endif // _MAINWINDOW_HPP_
