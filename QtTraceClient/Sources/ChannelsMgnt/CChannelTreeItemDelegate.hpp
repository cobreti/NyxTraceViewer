#ifndef CCHANNELTREEITEMDELEGATE_HPP
#define CCHANNELTREEITEMDELEGATE_HPP

#include <QItemDelegate>


class QTreeWidget;


class CChannelTreeItemDelegate : public QItemDelegate
{
public:
    CChannelTreeItemDelegate();
    virtual ~CChannelTreeItemDelegate();

    virtual QWidget* createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    virtual void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    void SetTreeWidget( QTreeWidget* pWidget )      { m_pTreeWidget = pWidget; }

protected:

    QTreeWidget*        m_pTreeWidget;
};

#endif // CCHANNELTREEITEMDELEGATE_HPP
