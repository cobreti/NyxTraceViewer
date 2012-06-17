#ifndef _TRACESWINDOW_HPP_
#define _TRACESWINDOW_HPP_

#include <QMainWindow>


class QToolButton;
class CTracesView;
class CPipesMgntPage;
class QLineEdit;
class CViewSearchEngine;


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
    void OnEmptyChannel( TraceClientCore::CTraceChannel* pChannel );
    void OnSearchTextChanged( const QString& text );
    void OnSearchNext();
    void OnSearchPrevious();

protected:

    virtual void closeEvent(QCloseEvent *);

protected:

    Ui::TracesWindow*       ui;

    CTracesView*            m_pTracesView;

    QToolButton*            m_pBtn_SourceFeeds;
    QToolButton*            m_pBtn_NewView;
    QToolButton*            m_pBtn_CloneView;
    QToolButton*            m_pBtn_SaveAs;

    QLineEdit*              m_pSearchText;
    QToolButton*            m_pBtn_SearchNext;
    QToolButton*            m_pBtn_SearchPrevious;

    CPipesMgntPage*         m_pPipesMgntPage;

    CViewSearchEngine*      m_pSearchEngine;

    static QMainWindow*     s_pDummyWnd;
};



#endif // _TRACESWINDOW_HPP_
