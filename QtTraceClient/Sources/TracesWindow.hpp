#ifndef _TRACESWINDOW_HPP_
#define _TRACESWINDOW_HPP_

#include <QMainWindow>

#include "View/ViewItemsNodeObjectsPool.hpp"
#include "View/Walkers/ViewItemsWalkerNodesPool.hpp"


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
    CTracesWindow();
    virtual ~CTracesWindow();

signals:

public slots:

    void OnSourceFeedsBtnClicked();
    void OnNewView();

protected:

    virtual void closeEvent(QCloseEvent *);

protected:

    Ui::TracesWindow*       ui;

    CTracesView*            m_pTracesView;

    QToolButton*            m_pBtn_SourceFeeds;
    QToolButton*            m_pBtn_NewView;
    QToolButton*            m_pBtn_CloneView;

    CPipesMgntPage*         m_pPipesMgntPage;

    CViewItemsNodeObjectsPool   m_ViewNodeObjectsPool;
    CViewItemsWalkerNodesPool   m_ViewItemsWalkerNodesPool;

};



#endif // _TRACESWINDOW_HPP_
