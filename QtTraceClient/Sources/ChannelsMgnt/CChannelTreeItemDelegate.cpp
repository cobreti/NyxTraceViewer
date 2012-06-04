#include "CChannelTreeItemDelegate.hpp"
#include "ChannelsMgnt/CChannelTreeItem.hpp"
#include "TraceChannel.hpp"

#include <qpainter.h>
#include <qapplication.h>

/**
 *
 */
CChannelTreeItemDelegate::CChannelTreeItemDelegate() : QItemDelegate(NULL),
    m_pTreeWidget(NULL)
{
}


/**
 *
 */
CChannelTreeItemDelegate::~CChannelTreeItemDelegate()
{
}


/**
 *
 */
QWidget* CChannelTreeItemDelegate::createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    if ( index.column() == 2 )
        return QItemDelegate::createEditor(parent, option, index);

    return NULL;
}


/**
 *
 */
void CChannelTreeItemDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    QItemDelegate::paint(painter, option, index);

    switch ( index.column() )
    {
        case 0:
            {
                QIcon   StateIcon(":/ChannelsMgnt/Channel");

                QItemDelegate::paint(painter, option, index);

                StateIcon.paint( painter, option.rect );
            }
            break;

        case 3:
            {
                CChannelTreeItem*      pItem = static_cast<CChannelTreeItem*>( m_pTreeWidget->topLevelItem(index.row()) );

                QIcon   StartStateIcon(":/ChannelsMgnt/StartChannel");
                QIcon   StopStateIcon(":/ChannelsMgnt/StopChannel");

                QItemDelegate::paint(painter, option, index);

                if ( pItem->TraceChannel()->Feeder()->IsRunning() )
                    StopStateIcon.paint( painter, option.rect );
                else
                    StartStateIcon.paint( painter, option.rect );
            }
            break;

        case 4:
        {
            QIcon   StateIcon(":/ChannelsMgnt/EmptyChannel");

            QItemDelegate::paint(painter, option, index);

            StateIcon.paint( painter, option.rect );
        }
        break;
    };
}
