#include "SettingsToolBar.hpp"
#include "TracesView.h"

#include <QToolButton>

/**
 *
 */
CSettingsToolBar::CSettingsToolBar( CTracesView* pView ) : QToolBar(pView),
m_pBtn_SourceFeeds(NULL)
{
    setFloatable(false);
    setMovable(false);
    setIconSize( QSize(16, 16));

    QIcon               PipeSourceIcon(":/MainWindow/Icons/PipeSource-icon.png");

    m_pBtn_SourceFeeds = new QToolButton();
    m_pBtn_SourceFeeds->setIcon(PipeSourceIcon);
    m_pBtn_SourceFeeds->setCheckable(true);
    addWidget(m_pBtn_SourceFeeds);

    connect( m_pBtn_SourceFeeds, SIGNAL(clicked()), this, SLOT(OnSourceFeedsBtnClicked()));
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
void CSettingsToolBar::OnSourceFeedsBtnClicked()
{
    emit sig_OnShowHideSettings(ViewEnums::eSourceFeeds, m_pBtn_SourceFeeds->isChecked());
}
