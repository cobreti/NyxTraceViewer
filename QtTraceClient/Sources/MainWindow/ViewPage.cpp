#include "ViewPage.hpp"
#include "ui_ViewPage.h"
#include "TracesView.h"

/**
 *
 */
CViewPage::CViewPage(QWidget* pParent) :
QDialog(pParent),
ui(new Ui::ViewPage()),
m_pView(NULL)
{
    ui->setupUi(this);

    setWindowFlags( Qt::Widget );

    ui->m_TopViewFrame->hide();
    ui->m_RightViewFrame->hide();
}


/**
 *
 */
//QFrame* CViewPage::ViewFrame() const
//{
//    return ui->m_ViewFrame;
//}


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
