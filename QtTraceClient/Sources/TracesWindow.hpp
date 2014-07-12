#ifndef _TRACESWINDOW_HPP_
#define _TRACESWINDOW_HPP_

#include <QMainWindow>
#include "View/Highlight/ViewItemPattern_Text.hpp"
#include "View/Highlight/ViewItemHighlighter.hpp"
#include "Controls/ToggleToolButton.h"
#include "Controls/ConnectionStatusToolButton.h"


class QToolButton;
class CTracesView;
class CPipesMgntPage;
class QLineEdit;
class CViewSearchEngine;
class CColorBtn;
class CHighlightsMgrWnd;
class CChannelSelection;

namespace TraceClientCore
{
    class CTraceChannel;
    class CTracesGroup;
}

namespace Ui
{
    class TracesWindow;
}


class CTracesWindow : public QMainWindow
{
    Q_OBJECT

public:
    CTracesWindow(CTracesWindow* pSrc);
    virtual ~CTracesWindow();

signals:

public slots:

    void OnSourceFeedsBtnClicked();
    void OnNewView();
    void OnCloneView();
    void OnSaveAs();
    void OnClear();
    void OnSearchTextChanged( const QString& text );
    void OnSearchNext();
    void OnSearchPrevious();
    void OnHighlightColorChanged(CColorBtn* pBtn);
    void OnAbout();
    void OnHighlightColorSelection();
    void OnSearch();
    void OnHideSearch();
    void OnShowMainWindow();
    void OnTracesGroupSelectionChanged(TraceClientCore::CTracesGroup* pGroup);
    void OnSettingsBtnStateChanged(CToggleToolButton::EState state);
    void OnDevicesSelectionBtnStateChanged(CToggleToolButton::EState state);
    void OnKeepAtEndBtnStateChanged(CToggleToolButton::EState state);
    void OnServerHeartbeatSuccess();
    void OnServerHeartbeatFailure();
    void OnKeepAtEndDisabled();
    void onSettingsPanelClosing();
    void onDevicesSelectionPanelClosing();

protected:

    virtual void closeEvent(QCloseEvent *);
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);
    virtual void moveEvent(QMoveEvent *);

protected:

    Ui::TracesWindow*       ui;

    CTracesView*            m_pTracesView;
    CChannelSelection*      m_pChannelSelection;

    QToolButton*            m_pBtn_MainWindow;
    QToolButton*            m_pBtn_SourceFeeds;
    QToolButton*            m_pBtn_NewView;
    QToolButton*            m_pBtn_CloneView;
    QToolButton*            m_pBtn_Search;
    QToolButton*            m_pBtn_HighlightColorSelection;
    QToolButton*            m_pBtn_SaveAs;
    QToolButton*            m_pBtn_Clear;
    QToolButton*            m_pBtn_About;
    CToggleToolButton*      m_pBtn_Settings;
    CToggleToolButton*      m_pBtn_Devices;
    CToggleToolButton*      m_pBtn_KeepAtEnd;
    CConnectionStatusToolButton*    m_pBtn_ConnectionStatus;

    QLineEdit*              m_pSearchText;
    QToolButton*            m_pBtn_HideSearch;
    QToolButton*            m_pBtn_SearchNext;
    QToolButton*            m_pBtn_SearchPrevious;
    CColorBtn*              m_pBtn_HighlightColor;

    CPipesMgntPage*         m_pPipesMgntPage;

    CViewSearchEngine*          m_pSearchEngine;
    CHighlightsMgrWnd*          m_pHighlightsMgrWnd;
    CViewItemHighlighterRef     m_refHighlighter;
    CViewItemPattern_TextRef    m_refTextPattern;

    QString                 m_WndName;

//    static QMainWindow*     s_pDummyWnd;
};



#endif // _TRACESWINDOW_HPP_
