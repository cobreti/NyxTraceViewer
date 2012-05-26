#ifndef _TRACESWINDOW_HPP_
#define _TRACESWINDOW_HPP_

#include <QMainWindow>


class QToolButton;
class CTracesView;
class CPipesMgntPage;



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

protected:

    virtual void closeEvent(QCloseEvent *);

protected:

    Ui::TracesWindow*       ui;

    CTracesView*            m_pTracesView;

    QToolButton*            m_pBtn_SourceFeeds;
    QToolButton*            m_pBtn_NewView;
    QToolButton*            m_pBtn_CloneView;
    QToolButton*            m_pBtn_SaveAs;

    CPipesMgntPage*         m_pPipesMgntPage;
};



#endif // _TRACESWINDOW_HPP_
