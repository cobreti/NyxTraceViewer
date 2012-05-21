#include "ViewPage.hpp"
#include "ui_ViewPage.h"
#include "TracesView.h"
#include "TraceClientApp.h"
#include "MainWindow/PipesMgntPage.hpp"

#include <QCloseEvent>
#include <QFileDialog>

/**
 *
 */
CViewPage::CViewPage(QWidget* pParent) :
QDialog(pParent),
ui(new Ui::ViewPage()),
m_pView(NULL),
m_pTBSettings(NULL),
m_pTBArea(NULL),
m_pViewLayout(NULL),
m_pPipesMgntPage(NULL)
{
    ui->setupUi(this);

    m_pTBArea = new QHBoxLayout();

    m_pTBSettings = new CSettingsToolBar(this);
    m_pTBSettings->setEnabled(true);
    m_pTBArea->addWidget(m_pTBSettings);
    m_pTBArea->setEnabled(true);

    m_pViewLayout = new QVBoxLayout();

    m_pViewLayout->addLayout(m_pTBArea);

    m_pPipesMgntPage = new CPipesMgntPage(this);
    m_pViewLayout->addWidget(m_pPipesMgntPage);
    m_pPipesMgntPage->hide();

    ui->m_ViewFrame->setLayout(m_pViewLayout);

    if ( pParent )
        setWindowFlags( Qt::Widget );

    ui->m_TitleFrame->hide();

    connect( m_pTBSettings, SIGNAL(sig_OnShowHideSettings(ViewEnums::ESettings, bool)), this, SLOT(OnShowHideSettings(ViewEnums::ESettings, bool)));
    connect( m_pTBSettings, SIGNAL(sig_OnPin(bool)), this, SLOT(OnPin(bool)));
    connect( m_pTBSettings, SIGNAL(sig_OnSave()), this, SLOT(OnSave()));

    m_pTBSettings->SetPinned(pParent != NULL);
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

    m_pTBSettings->show();
    m_pTBSettings->SetPinned(parent() != NULL);
    m_pViewLayout->addWidget(pView);

    if ( m_pPipesMgntPage->isVisible() )
    {
        m_pPipesMgntPage->show(m_pView->ViewCore());
    }

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
    {
        m_pView = NULL;
        m_pTBSettings->hide();
    }
}


/**
 *
 */
void CViewPage::OnShowHideSettings( ViewEnums::ESettings settings, bool bShow )
{
    switch ( settings )
    {
        case ViewEnums::eSourceFeeds:
            {
                if ( bShow )
                {
                    m_pPipesMgntPage->show(m_pView->ViewCore());
                }
                else
                {
                    m_pPipesMgntPage->hide();
                    setFocus();
                }
            }
            break;
    };
}


/**
 *
 */
void CViewPage::OnPin( bool bPinned )
{
    if ( bPinned )
    {
        close();
    }
    else
    {
        //CTraceClientApp::Instance().MainWindow()->UnpinView(m_pView);
    }
}


/**
 *
 */
void CViewPage::OnSave()
{
    QFileDialog     fileDlg;

    fileDlg.setNameFilter(tr("text (*.txt)"));
    fileDlg.setAcceptMode( QFileDialog::AcceptSave );
    fileDlg.setViewMode( QFileDialog::Detail);

    if ( fileDlg.exec())
    {
        QString     file = fileDlg.selectedFiles()[0];

        m_pView->Save(file);
    }
}


/**
 *
 */
void CViewPage::closeEvent( QCloseEvent* event )
{
    if ( parent() )
        event->ignore();

    //if ( m_pView )
    //    CTraceClientApp::Instance().MainWindow()->PinView(m_pView);
}
