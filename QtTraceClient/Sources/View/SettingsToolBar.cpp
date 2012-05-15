#include "SettingsToolBar.hpp"
//#include "TracesView.h"

#include <QToolButton>

/**
 *
 */
CSettingsToolBar::CSettingsToolBar( QWidget* pParent ) : QToolBar(pParent),
    m_pBtn_SourceFeeds(NULL),
    m_pBtn_SaveAs(NULL),
    m_pBtn_Pin(NULL),
    m_pSpacer(NULL)
{
    setFloatable(false);
    setMovable(false);
    setIconSize( QSize(16, 16));

    QIcon               PipeSourceIcon(":/MainWindow/Icons/PipeSource-icon.png");
    QIcon               SaveAsIcon(":/MainWindow/Icons/SaveAs.png");
    QIcon               PinIcon(":/View/pinwhite");

    m_pBtn_SaveAs = new QToolButton();
    m_pBtn_SaveAs->setIcon(SaveAsIcon);
    addWidget(m_pBtn_SaveAs);

    addSeparator();

    m_pBtn_SourceFeeds = new QToolButton();
    m_pBtn_SourceFeeds->setIcon(PipeSourceIcon);
    m_pBtn_SourceFeeds->setCheckable(true);
    addWidget(m_pBtn_SourceFeeds);


    m_pSpacer = new QWidget(this);
    m_pSpacer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    addWidget(m_pSpacer);

    m_pBtn_Pin = new QToolButton();
    m_pBtn_Pin->setIcon(PinIcon);
    m_pBtn_Pin->setAutoRaise(true);
    m_pBtn_Pin->setCheckable(true);
    addWidget(m_pBtn_Pin);


    connect( m_pBtn_SourceFeeds, SIGNAL(clicked()), this, SLOT(OnSourceFeedsBtnClicked()));
    connect( m_pBtn_Pin, SIGNAL(clicked()), this, SLOT(OnPinBtnClicked()));
    connect( m_pBtn_SaveAs, SIGNAL(clicked()), this, SLOT(OnSaveBtnClicked()));
}


/**
 *
 */
CSettingsToolBar::~CSettingsToolBar()
{
}


/**
 *
 */
void CSettingsToolBar::ForceShowSettings( ViewEnums::ESettings )
{
    m_pBtn_SourceFeeds->setChecked(true);
    OnSourceFeedsBtnClicked();
}


/**
 *
 */
void CSettingsToolBar::SetPinned(bool bPinned)
{
    m_pBtn_Pin->setChecked(bPinned);
}


/**
 *
 */
void CSettingsToolBar::OnSourceFeedsBtnClicked()
{
    emit sig_OnShowHideSettings(ViewEnums::eSourceFeeds, m_pBtn_SourceFeeds->isChecked());
}


/**
 *
 */
void CSettingsToolBar::OnPinBtnClicked()
{
    emit sig_OnPin(m_pBtn_Pin->isChecked());
}


/**
 *
 */
void CSettingsToolBar::OnSaveBtnClicked()
{
    emit sig_OnSave();
}

