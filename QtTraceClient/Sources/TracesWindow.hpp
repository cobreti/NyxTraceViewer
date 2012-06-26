#ifndef _TRACESWINDOW_HPP_
#define _TRACESWINDOW_HPP_

#include <QMainWindow>
#include "View/Highlight/ViewItemPattern_Text.hpp"
#include "View/Highlight/ViewItemHighlighter.hpp"


class QToolButton;
class CTracesView;
class CPipesMgntPage;
class QLineEdit;
class CViewSearchEngine;
class CColorBtn;
class CHighlightsMgrWnd;


namespace TraceClientCore
{
    class CTraceChannel;
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
    void OnSearchTextChanged( const QString& text );
    void OnSearchNext();
    void OnSearchPrevious();
    void OnHighlightColorChanged(CColorBtn* pBtn);
    void OnAbout();
    void OnHighlightColorSelection();
    void OnSearch();

protected:

    virtual void closeEvent(QCloseEvent *);

protected:

    Ui::TracesWindow*       ui;

    CTracesView*            m_pTracesView;

    QToolButton*            m_pBtn_SourceFeeds;
    QToolButton*            m_pBtn_NewView;
    QToolButton*            m_pBtn_CloneView;
    QToolButton*            m_pBtn_Search;
    QToolButton*            m_pBtn_HighlightColorSelection;
    QToolButton*            m_pBtn_SaveAs;
    QToolButton*            m_pBtn_About;

    QLineEdit*              m_pSearchText;
    QToolButton*            m_pBtn_SearchNext;
    QToolButton*            m_pBtn_SearchPrevious;
    CColorBtn*              m_pBtn_HighlightColor;

    CPipesMgntPage*         m_pPipesMgntPage;

    CViewSearchEngine*          m_pSearchEngine;
    CHighlightsMgrWnd*          m_pHighlightsMgrWnd;
    CViewItemHighlighterRef     m_refHighlighter;
    CViewItemPattern_TextRef    m_refTextPattern;

    static QMainWindow*     s_pDummyWnd;
};



#endif // _TRACESWINDOW_HPP_
