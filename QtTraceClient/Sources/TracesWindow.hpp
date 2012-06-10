#ifndef _TRACESWINDOW_HPP_
#define _TRACESWINDOW_HPP_

#include <QMainWindow>


class QToolButton;
class CTracesView;
class CPipesMgntPage;
class QLineEdit;

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

    CPipesMgntPage*         m_pPipesMgntPage;

    static QMainWindow*     s_pDummyWnd;
};



#endif // _TRACESWINDOW_HPP_
