#ifndef _HIGHLIGHTTREEITEMDELEGATE_HPP_
#define _HIGHLIGHTTREEITEMDELEGATE_HPP_


#include <QItemDelegate>

class QTreeWidget;


/**
 *
 */
class CHighlightTreeItemDelegate : public QItemDelegate
{
    Q_OBJECT;

public:
    CHighlightTreeItemDelegate(QTreeWidget* pTreeWidget);
    virtual ~CHighlightTreeItemDelegate();

    virtual QWidget* createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    virtual void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;

protected:

    QTreeWidget*        m_pTreeWidget;
};





#endif // _HIGHLIGHTTREEITEMDELEGATE_HPP_

