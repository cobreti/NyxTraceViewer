#include "ViewPage.hpp"
#include "ui_ViewPage.h"
#include "TracesView.h"
#include "TraceClientApp.hpp"
#include "MainWindow.h"

#include <QCloseEvent>

/**
 *
 */
CViewPage::CViewPage(QWidget* pParent) :
QDialog(pParent),
ui(new Ui::ViewPage()),
m_pView(NULL)
{
    ui->setupUi(this);

    if ( pParent )
        setWindowFlags( Qt::Widget );
}


/**
 *
 */
CViewPage::~CViewPage()
{
}



/**
 *
 */
void CViewPage::show( CTracesView* pView )
{
    if ( m_pView )
        m_pView->hide();

    m_pView = pView;

    ui->m_ViewFrame->layout()->addWidget(pView);

    QDialog::show();
    m_pView->show();
    m_pView->setFocus(Qt::OtherFocusReason);
}


/**
 *
 */
void CViewPage::hide()
{
    if  ( m_pView )
    {
        m_pView->hide();
        m_pView = NULL;
    }

    QDialog::hide();
}


/**
 *
 */
void CViewPage::DetachView( CTracesView* pView )
{
    if ( m_pView == pView )
        m_pView = NULL;
}


/**
 *
 */
void CViewPage::closeEvent( QCloseEvent* event )
{
    event->ignore();

    if ( m_pView )
        CTraceClientApp::Instance().MainWindow()->PinView(m_pView);
}
