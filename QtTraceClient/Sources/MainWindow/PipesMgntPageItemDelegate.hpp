#ifndef _INC_PIPESMGNTPAGEITEMDELEGATE_HPP_
#define _INC_PIPESMGNTPAGEITEMDELEGATE_HPP_

#include <QItemDelegate>

class QTreeWidget;

class CPipesMgntPageItemDelegate : public QItemDelegate
{
    Q_OBJECT;

public:
    CPipesMgntPageItemDelegate();
    virtual ~CPipesMgntPageItemDelegate();

    virtual QWidget* createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    virtual void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    void SetTreeWidget( QTreeWidget* pWidget )      { m_pTreeWidget = pWidget; }

protected:

    QTreeWidget*        m_pTreeWidget;
};


#endif // _INC_PIPESMGNTPAGEITEMDELEGATE_HPP_
