#ifndef _SettingsToolBar_HPP_
#define _SettingsToolBar_HPP_

#include <QToolbar>

#include "View/ViewEnums.hpp"

class CTracesView;
class QToolButton;

/**
 *
 */
class CSettingsToolBar : public QToolBar
{
    Q_OBJECT

public:


public:
    CSettingsToolBar( CTracesView* pView );
    virtual ~CSettingsToolBar();

    void ForceShowSettings( ViewEnums::ESettings settings );

public slots:

    void OnSourceFeedsBtnClicked();

Q_SIGNALS:

    void sig_OnShowHideSettings(ViewEnums::ESettings settings, bool bShow);

protected:

    QToolButton*            m_pBtn_SourceFeeds;
};

#endif // _SettingsToolBar_HPP_
