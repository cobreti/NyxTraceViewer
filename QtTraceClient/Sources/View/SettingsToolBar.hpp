#ifndef _SettingsToolBar_HPP_
#define _SettingsToolBar_HPP_

#include <QToolBar>

#include "View/ViewEnums.hpp"

//class CTracesView;
class QToolButton;

/**
 *
 */
class CSettingsToolBar : public QToolBar
{
    Q_OBJECT


public:
    CSettingsToolBar( QWidget* pParent );
    virtual ~CSettingsToolBar();

    void ForceShowSettings( ViewEnums::ESettings settings );

    void SetPinned(bool bPinned);

public slots:

    void OnSourceFeedsBtnClicked();
    void OnPinBtnClicked();
    void OnSaveBtnClicked();

Q_SIGNALS:

    void sig_OnShowHideSettings(ViewEnums::ESettings settings, bool bShow);
    void sig_OnPin(bool bPinned);
    void sig_OnSave();

protected:

    QToolButton*            m_pBtn_SourceFeeds;
    QToolButton*            m_pBtn_SaveAs;
    QToolButton*            m_pBtn_Pin;

    QWidget*                m_pSpacer;
};

#endif // _SettingsToolBar_HPP_
