#include "MainWindow.hpp"

#include "ui_MainWindow.h"


/**
 *
 */
CMainWindow::CMainWindow() : QMainWindow(),
ui( new Ui::MainWindow())
{
    ui->setupUi(this);
}


/**
 *
 */
CMainWindow::~CMainWindow()
{
}

