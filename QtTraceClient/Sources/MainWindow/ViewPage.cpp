#include "ViewPage.hpp"
#include "ui_ViewPage.h"
#include "TracesView.h"
#include "TraceClientApp.hpp"
#include "MainWindow.h"
#include "MainWindow/PipesMgntPage.hpp"

#include <QCloseEvent>

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
m_pBtnPin(NULL),
m_pPipesMgntPage(NULL)
{
    ui->setupUi(this);

    m_pTBArea = new QHBoxLayout();

    m_pTBSettings = new CSettingsToolBar(this);
    m_pTBSettings->setEnabled(true);
    m_pTBArea->addWidget(m_pTBSettings);
    m_pTBArea->setEnabled(true);

    m_pViewLayout = new QVBoxLayout();

    QIcon   PinIcon(":/View/pinwhite");
    m_pBtnPin = new QToolButton(this);
    m_pBtnPin->setIcon(PinIcon);
    m_pBtnPin->setIconSize( QSize(16, 16) );
    m_pBtnPin->setAutoRaise(true);
    m_pBtnPin->setCheckable(true);
    m_pBtnPin->setChecked(pParent != NULL);
    m_pBtnPin->resize(20, 20);
    m_pTBArea->addWidget(m_pBtnPin);

    m_pViewLayout->addLayout(m_pTBArea);

    m_pPipesMgntPage = new CPipesMgntPage(this);
    m_pViewLayout->addWidget(m_pPipesMgntPage);
    m_pPipesMgntPage->hide();

    ui->m_ViewFrame->setLayout(m_pViewLayout);

    if ( pParent )
        setWindowFlags( Qt::Widget );

    ui->m_TitleFrame->hide();

    connect( m_pTBSettings, SIGNAL(sig_OnShowHideSettings(ViewEnums::ESettings, bool)), this, SLOT(OnShowHideSettings(ViewEnums::ESettings, bool)));
    connect( m_pBtnPin, SIGNAL(clicked(bool)), this, SLOT(OnPinBtnClicked(bool)));
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
    m_pBtnPin->show();
    m_pBtnPin->setChecked(parent() != NULL);
    m_pViewLayout->addWidget(pView);

    if ( m_pPipesMgntPage->isVisible() )
    {
        m_pPipesMgntPage->show(&m_pView->Doc());
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
        m_pBtnPin->hide();
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
                    m_pPipesMgntPage->show(&m_pView->Doc());
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
void CViewPage::OnPinBtnClicked( bool checked )
{
    if ( checked )
    {
        close();
    }
    else
    {
        CTraceClientApp::Instance().MainWindow()->UnpinView(m_pView);
    }
}


/**
 *
 */
void CViewPage::closeEvent( QCloseEvent* event )
{
    if ( parent() )
        event->ignore();

    if ( m_pView )
        CTraceClientApp::Instance().MainWindow()->PinView(m_pView);
}
