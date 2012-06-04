#include "TraceClientCoreModule.hpp"

#include "ui_ChannelsMgnt.h"
#include "ChannelsMgnt.hpp"
#include "ChannelsMgnt/CChannelTreeItem.hpp"
#include "ChannelsMgnt/CChannelTreeItemDelegate.hpp"

/**
 *
 */
CChannelsMgnt::CChannelsMgnt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelsMgnt),
    m_pChannelTreeItemDelegate(NULL)
{
    ui->setupUi(this);

    setWindowFlags( Qt::Popup );

    ui->ChannelsTreeWidget->setColumnWidth(0, 48);
    ui->ChannelsTreeWidget->setColumnWidth(1, 48 );
    ui->ChannelsTreeWidget->setColumnWidth(2, 48 );

    m_pChannelTreeItemDelegate = new CChannelTreeItemDelegate();
    m_pChannelTreeItemDelegate->SetTreeWidget( ui->ChannelsTreeWidget );
    ui->ChannelsTreeWidget->setItemDelegateForColumn(0, m_pChannelTreeItemDelegate);
    ui->ChannelsTreeWidget->setItemDelegateForColumn(1, m_pChannelTreeItemDelegate);
    ui->ChannelsTreeWidget->setItemDelegateForColumn(2, m_pChannelTreeItemDelegate);
    ui->ChannelsTreeWidget->setItemDelegateForColumn(3, m_pChannelTreeItemDelegate);
}


/**
 *
 */
CChannelsMgnt::~CChannelsMgnt()
{
    delete ui;
}


/**
 *
 */
void CChannelsMgnt::Show(int x, int y)
{
    LoadChannels();

    move(x, y);
    show();
}


/**
 *
 */
void CChannelsMgnt::LoadChannels()
{
    TraceClientCore::CModule&                               rModule = TraceClientCore::CModule::Instance();
    TraceClientCore::CTraceChannelsList                     ChannelsList;
    TraceClientCore::CTraceChannelsList::const_iterator     ChannelPos;

    rModule.TraceChannels().GetChannelsList(ChannelsList);

    ui->ChannelsTreeWidget->clear();

    for ( ChannelPos = ChannelsList.begin(); ChannelPos != ChannelsList.end(); ++ ChannelPos )
    {
//        MainWindow::CPoolTreeItem*                  pItem = new MainWindow::CPoolTreeItem();
        CChannelTreeItem*                           pItem = new CChannelTreeItem();
        TraceClientCore::CTraceChannel&             rChannel = (*ChannelPos).Channel();

        pItem->SetChannel( &rChannel );
//        pItem->setFlags( Qt::ItemIsEditable | pItem->flags() );
        pItem->setForeground( 0, QBrush(QColor(150, 0, 0)) );

        if ( rChannel.Feeder().Valid() )
        {
            if ( rChannel.Feeder()->IsRunning() )
            {
                pItem->setFlags( pItem->flags() & ~Qt::ItemIsEditable );
                pItem->setForeground(0, QBrush(QColor(0, 150, 0)));
            }
            else
            {
//                pItem->setFlags( Qt::ItemIsEditable | pItem->flags() );
                pItem->setForeground(0, QBrush(QColor(150, 0, 0)));
            }
        }

//        if ( m_pViewCore->Contains(*rChannel.Pool()) )
//            pItem->setCheckState(0, Qt::Checked );
//        else
//            pItem->setCheckState(0, Qt::Unchecked );

        ui->ChannelsTreeWidget->insertTopLevelItem(ui->ChannelsTreeWidget->topLevelItemCount(), pItem );
    }
}
