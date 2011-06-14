#include "ViewTreeItem.hpp"
#include "Document/TracesDocument.hpp"
#include "TracesView.h"

namespace MainWindow
{
    /**
     *
     */
    CViewTreeItem::CViewTreeItem( QTreeWidgetItem* parentItem, CTracesDocument* pDoc, CTracesView* pView ) :
    QTreeWidgetItem(parentItem),
    m_pView(pView),
    m_pDocument(pDoc)
    {
        setText(0, pView->Name());
        m_eType = CViewTreeItem::eCT_View;
    }


    /**
     *
     */
    CViewTreeItem::CViewTreeItem( QTreeWidgetItem* parentItem, CTracesDocument* pDoc ) :
    QTreeWidgetItem(parentItem),
    m_pView(NULL),
    m_pDocument(pDoc)
    {
        setText(0, pDoc->Name());
        m_eType = CViewTreeItem::eCT_Document;
    }


    /**
     *
     */
    CViewTreeItem::CViewTreeItem( QTreeWidgetItem* parentItem, CTracesView* pView ) :
    QTreeWidgetItem(parentItem),
    m_pView(pView),
    m_pDocument(NULL)
    {
        setText(0, pView->Name());
        m_eType = CViewTreeItem::eCT_View;
    }


    /**
     *
     */
    CViewTreeItem::CViewTreeItem( QTreeWidgetItem* parentItem, const char* szText ) :
    QTreeWidgetItem(parentItem),
    m_pView(NULL),
    m_pDocument(NULL)
    {
        setText(0, szText);
        m_eType = CViewTreeItem::eCT_Root;
    }
}
