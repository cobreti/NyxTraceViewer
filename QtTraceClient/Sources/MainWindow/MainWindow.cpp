#include "MainWindow.hpp"
#include "TracesWindow.hpp"
#include "ChannelsMgnt/ChannelsMgnt.hpp"

#include <QToolButton>

#include "ui_MainWindow.h"


/**
 *
 */
CMainWindow::CMainWindow() : QMainWindow(),
    ui( new Ui::MainWindow()),
    m_pBtn_NewView(NULL),
    m_pBtn_Channels(NULL)
{
    ui->setupUi(this);

    QIcon       NewViewIcon(":/MainWindow/Icons/View-icon.png");
    QIcon       ChannelsIcon(":/MainWindow/Icons/PipeSource-icon.png");

    m_pBtn_NewView = new QToolButton();
    m_pBtn_NewView->setIcon(NewViewIcon);

    m_pBtn_Channels = new QToolButton();
    m_pBtn_Channels->setIcon(ChannelsIcon);

    ui->MainToolBar->addWidget(m_pBtn_Channels);
    ui->MainToolBar->addSeparator();
    ui->MainToolBar->addWidget(m_pBtn_NewView);
    ui->MainToolBar->setIconSize( QSize(16, 16) );

    connect( m_pBtn_NewView, SIGNAL(clicked()), this, SLOT(OnNewTracesWindow()));
    connect( m_pBtn_Channels, SIGNAL(clicked()), this, SLOT(OnChannelsMgnt()));
}


/**
 *
 */
CMainWindow::~CMainWindow()
{
}


/**
 *
 */
void CMainWindow::OnNewTracesWindow()
{
    CTracesWindow*  pWnd = new CTracesWindow(NULL);
    pWnd->show();
}


/**
 *
 */
void CMainWindow::OnChannelsMgnt()
{
    QPoint              pt( m_pBtn_Channels->frameGeometry().left(), m_pBtn_Channels->frameGeometry().bottom() );

    pt = mapToGlobal(pt);

    CChannelsMgnt::Show(this, pt);
}