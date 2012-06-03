#ifndef _MAINWINDOW_HPP_
#define _MAINWINDOW_HPP_

#include <QMainWindow>


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

protected:

    Ui::MainWindow*     ui;
};




#endif // _MAINWINDOW_HPP_
