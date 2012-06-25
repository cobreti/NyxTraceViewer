#ifndef _HIGHLIGHTSMGRWND_H_
#define _HIGHLIGHTSMGRWND_H_

#include <QWidget>
#include <QTreeWidgetItem>

namespace Ui
{
    class HighlightsMgrWnd;
}

class CTracesView;
class CHighlightTreeItemDelegate;
class QTreeWidgetItem;
class CViewSearchEngine;


/**
 *
 */
class CHighlightsMgrWnd : public QWidget
{
    Q_OBJECT

public:
    CHighlightsMgrWnd(CViewSearchEngine* pSearchEngine, QWidget* parent);
    virtual ~CHighlightsMgrWnd();

    void Show(const QPoint& pt, const QSize& size);

public slots:

    void OnItemChanged(QTreeWidgetItem* pItem, int column);

protected:

    void showEvent(QShowEvent*);
    void resizeEvent(QResizeEvent*);

protected:

    Ui::HighlightsMgrWnd*           ui;
    CViewSearchEngine*              m_pSearchEngine;
    CHighlightTreeItemDelegate*     m_pTreeItemDelegate;
};


#endif // _HIGHLIGHTSMGRWND_H_
