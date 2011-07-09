#include "ViewTreeItem.hpp"
#include "TracesView.h"

namespace MainWindow
{
    /**
     *
     */
    CViewTreeItem::CViewTreeItem( QTreeWidgetItem* parentItem, CTracesView* pView ) :
    QTreeWidgetItem(parentItem),
    m_pView(pView)
    {
        setText(0, pView->Name());
    }


    /**
     *
     */
    CViewTreeItem::CViewTreeItem( QTreeWidgetItem* parentItem, const char* szText ) :
    QTreeWidgetItem(parentItem),
    m_pView(NULL)
    {
        setText(0, szText);
    }
}
