
#include "DevicesSelectionPanel.h"
#include "TraceClientApp.h"
#include "DevicesMgr.h"
#include "ServerAccess/TraceServerPortal.h"

#include "ui_DevicesSelection.h"

#include <QApplication>


/**
 * @brief CDevicesSelection::CDevicesSelection
 */
CDevicesSelectionPanel::CDevicesSelectionPanel() : QWidget(),
    ui(new Ui::DevicesSelection())
{
    ui->setupUi(this);

    XItemDelegate* pDelegate = new XItemDelegate();
    pDelegate->setParent(ui->devicesList);
    ui->devicesList->setItemDelegateForColumn(0, pDelegate);
    ui->devicesList->setItemDelegateForColumn(1, pDelegate);

    connect(    ui->devicesList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
                this, SLOT(onItemDoubleClicked(QTreeWidgetItem*,int)) );


//    CDevice         device;
//    device.id() = 1;
//    device.name() = "test";
//    device.alias() = "alias value";
//    XTreeItem* pItem = new XTreeItem(device);
//    ui->devicesList->addTopLevelItem(pItem);
}


/**
 * @brief CDevicesSelection::~CDevicesSelection
 */
CDevicesSelectionPanel::~CDevicesSelectionPanel()
{

}


void CDevicesSelectionPanel::onItemDoubleClicked(QTreeWidgetItem *pItem, int column)
{
    if ( column == 0 )
    {
        XTreeItem*      pTreeItem = static_cast<XTreeItem*>(pItem);
        pTreeItem->setSelected( !pTreeItem->isSelected() );
    }
}


void CDevicesSelectionPanel::onDeviceAdded(const CDevice &device)
{
    XTreeItem* pItem = new XTreeItem(device);
    ui->devicesList->addTopLevelItem(pItem);
}


void CDevicesSelectionPanel::onDeviceRemoved(const CDevice &device)
{

}


void CDevicesSelectionPanel::showEvent(QShowEvent *)
{
    QApplication*   app = static_cast<QApplication*>(QApplication::instance());
    CDevicesMgr&    rDevicesMgr = CTraceClientApp::Instance().DevicesMgr();

    connect(    &rDevicesMgr, SIGNAL(deviceAdded(CDevice)), this, SLOT(onDeviceAdded(CDevice)));
    connect( app, SIGNAL(focusChanged(QWidget*,QWidget*)), this, SLOT(onFocusChanged(QWidget*,QWidget*)) );

    CTraceClientApp::Instance().TraceServerPortal().getDevices();
}


void CDevicesSelectionPanel::hideEvent(QHideEvent *)
{
    QApplication*   app = static_cast<QApplication*>(QApplication::instance());
    CDevicesMgr&    rDevicesMgr = CTraceClientApp::Instance().DevicesMgr();

    disconnect( app, SIGNAL(focusChanged(QWidget*,QWidget*)), this, SLOT(onFocusChanged(QWidget*,QWidget*)) );
    disconnect( &rDevicesMgr, SIGNAL(deviceAdded(CDevice)), this, SLOT(onDeviceAdded(CDevice)) );
}



CDevicesSelectionPanel::XTreeItem::XTreeItem(const CDevice& device) : QTreeWidgetItem(),
    m_Device(device),
    m_bSelected(false)

{
    setText(1, device.alias());
}


CDevicesSelectionPanel::XTreeItem::~XTreeItem()
{

}


void CDevicesSelectionPanel::XTreeItem::setSelected(bool bSelected)
{
    m_bSelected = bSelected;
    setData(0, Qt::UserRole, QVariant(m_bSelected));
}


CDevicesSelectionPanel::XItemDelegate::XItemDelegate() : QItemDelegate()
{
    m_CheckIcon = QIcon(":/devicesSelectionPanel/Check-Icon");
}


CDevicesSelectionPanel::XItemDelegate::~XItemDelegate()
{

}


void CDevicesSelectionPanel::XItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    switch (index.column())
    {
        case 0:
        {
            bool bSelected = index.data(Qt::UserRole).toBool();

            if ( bSelected )
            {
                m_CheckIcon.paint(painter, option.rect);
            }
        }
        break;

        default:
        {
            QItemDelegate::paint(painter, option, index);
        }
        break;
    }
}


QSize CDevicesSelectionPanel::XItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QItemDelegate::sizeHint(option, index);
}

