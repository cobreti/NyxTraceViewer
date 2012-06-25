#ifndef _HIGHLIGHTSMGRWND_H_
#define _HIGHLIGHTSMGRWND_H_

#include <QWidget>

namespace Ui
{
    class HighlightsMgrWnd;
}

class CTracesView;
class CHighlightTreeItemDelegate;


/**
 *
 */
class CHighlightsMgrWnd : public QWidget
{
public:
    CHighlightsMgrWnd(CTracesView* pView, QWidget* parent);
    virtual ~CHighlightsMgrWnd();

    void Show(const QPoint& pt, const QSize& size);

protected:

    void showEvent(QShowEvent*);
    void resizeEvent(QResizeEvent*);

protected:

    Ui::HighlightsMgrWnd*           ui;
    CTracesView*                    m_pView;
    CHighlightTreeItemDelegate*     m_pTreeItemDelegate;
};


#endif // _HIGHLIGHTSMGRWND_H_
