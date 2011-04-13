#include "DocViewTreeItem.hpp"
#include "TracesDocument.hpp"
#include "TracesView.h"

namespace MainWindow
{
    /**
     *
     */
    CDocViewTreeItem::CDocViewTreeItem( QTreeWidgetItem* parentItem, CTracesDocument* pDoc, CTracesView* pView ) :
    QTreeWidgetItem(parentItem),
    m_pView(pView),
    m_pDocument(pDoc)
    {
        setText(0, pView->Name());
        m_eType = CDocViewTreeItem::eCT_View;
    }


    /**
     *
     */
    CDocViewTreeItem::CDocViewTreeItem( QTreeWidgetItem* parentItem, CTracesDocument* pDoc ) :
    QTreeWidgetItem(parentItem),
    m_pView(NULL),
    m_pDocument(pDoc)
    {
        setText(0, pDoc->Name());
        m_eType = CDocViewTreeItem::eCT_Document;
    }


    /**
     *
     */
    CDocViewTreeItem::CDocViewTreeItem( QTreeWidgetItem* parentItem, const char* szText ) :
    QTreeWidgetItem(parentItem),
    m_pView(NULL),
    m_pDocument(NULL)
    {
        setText(0, szText);
        m_eType = CDocViewTreeItem::eCT_Root;
    }
}
