#include "PipesMgntPageItemDelegate.hpp"
#include "PoolTreeItem.hpp"
#include "TraceChannel.hpp"

#include <qpainter.h>
#include <qapplication.h>

/**
 *
 */
CPipesMgntPageItemDelegate::CPipesMgntPageItemDelegate() : QItemDelegate(NULL), m_pTreeWidget(NULL)
{
}


/**
 *
 */
CPipesMgntPageItemDelegate::~CPipesMgntPageItemDelegate()
{
}


/**
 *
 */
QWidget* CPipesMgntPageItemDelegate::createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    if ( index.column() == 3 )
        return QItemDelegate::createEditor(parent, option, index);

    return NULL;
}


/**
 *
 */
void CPipesMgntPageItemDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    QItemDelegate::paint(painter, option, index);

    switch ( index.column() )
    {
        case 1:
            {
                QIcon   StateIcon(":/TracesWindow/Icons/PipeSource-icon.png");

                QItemDelegate::paint(painter, option, index);

                StateIcon.paint( painter, option.rect );
            }
            break;

        case 2:
            {
                MainWindow::CPoolTreeItem*      pItem = static_cast<MainWindow::CPoolTreeItem*>( m_pTreeWidget->topLevelItem(index.row()) );

                QIcon   StartStateIcon(":/TracesWindow/Icons/StartPipe-icon.png");
                QIcon   StopStateIcon(":/TracesWindow/Icons/StopPipe-icon.png");

                QItemDelegate::paint(painter, option, index);

                if ( pItem->TraceChannel()->Feeder()->IsRunning() )
                    StopStateIcon.paint( painter, option.rect );
                else
                    StartStateIcon.paint( painter, option.rect );
            }
            break;
    };
}
