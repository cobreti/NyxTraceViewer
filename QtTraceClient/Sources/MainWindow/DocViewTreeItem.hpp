#ifndef _DOCVIEWTREEITEM_HPP_
#define _DOCVIEWTREEITEM_HPP_

#include <QTreeWidgetItem>


class CTracesView;
class CTracesDocument;

namespace MainWindow
{
    /**
    *
    */
    class CDocViewTreeItem : public QTreeWidgetItem
    {
    public:

        enum ContentType
        {
            eCT_Root,
            eCT_Document,
            eCT_View
        };

    public:
        CDocViewTreeItem( QTreeWidgetItem* parentItem, CTracesDocument* pDoc, CTracesView* pView );
        CDocViewTreeItem( QTreeWidgetItem* parentItem, CTracesDocument* pDoc );
        CDocViewTreeItem( QTreeWidgetItem* parentItem, const char* szText );

        ContentType                 Type() const            { return m_eType; }
        CTracesView*                View() const            { return m_pView; }
        CTracesDocument*            Document() const        { return m_pDocument; }

    private:

        CTracesView*                m_pView;
        CTracesDocument*            m_pDocument;
        ContentType                 m_eType;
    };
}

#endif // _DOCVIEWTREEITEM_HPP_
