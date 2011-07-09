#ifndef _VIEWTREEITEM_HPP_
#define _VIEWTREEITEM_HPP_

#include <QTreeWidgetItem>


class CTracesView;

namespace MainWindow
{
    /**
    *
    */
    class CViewTreeItem : public QTreeWidgetItem
    {
    public:
        CViewTreeItem( QTreeWidgetItem* parentItem, CTracesView* pView );
        CViewTreeItem( QTreeWidgetItem* parentItem, const char* szText );

        CTracesView*                View() const            { return m_pView; }

    private:

        CTracesView*                m_pView;
    };

}

#endif // _DOCVIEWTREEITEM_HPP_
