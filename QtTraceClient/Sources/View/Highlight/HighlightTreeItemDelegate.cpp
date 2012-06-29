#include "HighlightTreeItemDelegate.hpp"
#include "HighlightTreeItem.hpp"

#include <QtGui>
#include <QPainter>

/**
 *
 */
CHighlightTreeItemDelegate::CHighlightTreeItemDelegate(QTreeWidget* pTreeWidget) : QItemDelegate(NULL), 
    m_pTreeWidget(pTreeWidget)
{
}


/**
 *
 */
CHighlightTreeItemDelegate::~CHighlightTreeItemDelegate()
{
}


/**
 *
 */
QWidget* CHighlightTreeItemDelegate::createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    if ( index.column() == 1 )
        return QItemDelegate::createEditor(parent, option, index);

    return NULL;
}


/**
 *
 */
void CHighlightTreeItemDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    QItemDelegate::paint(painter, option, index);

    CHighlightTreeItem*     pItem = static_cast<CHighlightTreeItem*>(m_pTreeWidget->topLevelItem(index.row()));

    switch ( index.column() )
    {
        case 0:
            {
                CColorBtn*  pBtn = pItem->ColorBtn();
                pBtn->setParent(m_pTreeWidget);
                pBtn->move(option.rect.left()+1, option.rect.top()+1);
                pBtn->resize(option.rect.width()-2, option.rect.height()-2);
                pBtn->show();
            }
            break;

        case 2:
            {
                QToolButton*  pBtn = pItem->SearchNextBtn();
                pBtn->setParent(m_pTreeWidget);
                pBtn->move(option.rect.left()+1, option.rect.top()+1);
                pBtn->resize(option.rect.width()-2, option.rect.height()-2);
                pBtn->show();

                pBtn->setEnabled( !pItem->text(1).isEmpty() );
            }
            break;

        case 3:
            {
                QToolButton*  pBtn = pItem->SearchPreviousBtn();
                pBtn->setParent(m_pTreeWidget);
                pBtn->move(option.rect.left()+1, option.rect.top()+1);
                pBtn->resize(option.rect.width()-2, option.rect.height()-2);
                pBtn->show();

                pBtn->setEnabled( !pItem->text(1).isEmpty() );
            }
            break;
    };

    //switch ( index.column() )
    //{
    //    case 1:
    //        {
    //            QIcon   StateIcon(":/TracesWindow/Icons/PipeSource-icon.png");

    //            QItemDelegate::paint(painter, option, index);

    //            StateIcon.paint( painter, option.rect );
    //        }
    //        break;

    //    case 2:
    //        {
    //            MainWindow::CPoolTreeItem*      pItem = static_cast<MainWindow::CPoolTreeItem*>( m_pTreeWidget->topLevelItem(index.row()) );

    //            QIcon   StartStateIcon(":/TracesWindow/Icons/StartPipe-icon.png");
    //            QIcon   StopStateIcon(":/TracesWindow/Icons/StopPipe-icon.png");

    //            QItemDelegate::paint(painter, option, index);

    //            if ( pItem->TraceChannel()->Feeder()->IsRunning() )
    //                StopStateIcon.paint( painter, option.rect );
    //            else
    //                StartStateIcon.paint( painter, option.rect );
    //        }
    //        break;
    //};
}
