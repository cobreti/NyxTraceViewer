#include "TracesWindow.hpp"
#include "TracesView.h"
#include "MainWindow/PipesMgntPage.hpp"

#include "ui_TracesWindow.h"

#include <QToolButton>


/**
 *
 */
CTracesWindow::CTracesWindow() : QMainWindow(),
ui( new Ui::TracesWindow() ),
m_pTracesView(NULL),
m_pBtn_SourceFeeds(NULL),
m_pPipesMgntPage(NULL)
{
    ui->setupUi(this);

    QIcon               PipeSourceIcon(":/MainWindow/Icons/PipeSource-icon.png");

    m_pTracesView = new CTracesView(this);
    m_pPipesMgntPage = new CPipesMgntPage(this);
    m_pPipesMgntPage->hide();

    ui->gridLayout->addWidget(m_pPipesMgntPage);
    ui->gridLayout->addWidget(m_pTracesView);

    m_pBtn_SourceFeeds = new QToolButton();
    m_pBtn_SourceFeeds->setIconSize( QSize(32, 32) );
    m_pBtn_SourceFeeds->setIcon(PipeSourceIcon);
    m_pBtn_SourceFeeds->setCheckable(true);

    ui->toolBar->addWidget(m_pBtn_SourceFeeds);

    connect( m_pBtn_SourceFeeds, SIGNAL(clicked()), this, SLOT(OnSourceFeedsBtnClicked()));
}


/**
 *
 */
CTracesWindow::~CTracesWindow()
{
}


/**
 *
 */
void CTracesWindow::OnSourceFeedsBtnClicked()
{
    if ( m_pBtn_SourceFeeds->isChecked() )
    {
        m_pPipesMgntPage->show(m_pTracesView->ViewCore());
        //m_pTracesView->hide();
    }
    else
    {
        m_pPipesMgntPage->hide();
        //m_pTracesView->show();
    }
}


