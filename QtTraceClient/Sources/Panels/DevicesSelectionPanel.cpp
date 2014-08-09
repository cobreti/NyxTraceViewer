
#include "DevicesSelectionPanel.h"
#include "TraceClientApp.h"
#include "DevicesMgr.h"
#include "ServerAccess/TraceServerPortal.h"

#include "ui_DevicesSelection.h"

#include <QApplication>
#include <QMouseEvent>


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
}


/**
 * @brief CDevicesSelection::~CDevicesSelection
 */
CDevicesSelectionPanel::~CDevicesSelectionPanel()
{

}


bool CDevicesSelectionPanel::eventFilter(QObject * pWatched, QEvent * pEvent)
{
    if ( pEvent->type() == QEvent::MouseButtonPress )
    {
        QMouseEvent*    pMouseEvent = static_cast<QMouseEvent*>(pEvent);
        QRect           rcWidget = QRect( mapToGlobal(rect().topLeft()), mapToGlobal(rect().bottomRight()) );
        QPoint          mousePos = pMouseEvent->globalPos();

        if ( rcWidget.contains(mousePos) )
        {
            return QObject::eventFilter(pWatched, pEvent);
        }
        else
        {
            return true;
        }
    }
    else if ( pEvent->type() == QEvent::MouseButtonRelease )
    {
        QMouseEvent*    pMouseEvent = static_cast<QMouseEvent*>(pEvent);
        QRect           rcWidget = QRect( mapToGlobal(rect().topLeft()), mapToGlobal(rect().bottomRight()) );
        QPoint          mousePos = pMouseEvent->globalPos();

        if ( rcWidget.contains(mousePos) )
        {
            return QObject::eventFilter(pWatched, pEvent);
        }
        else
        {
            emit closing();
            this->close();
            return true;
        }
    }

    return QObject::eventFilter(pWatched, pEvent);
}


void CDevicesSelectionPanel::onItemDoubleClicked(QTreeWidgetItem *pItem, int column)
{
    if ( column == 0 )
    {
        XTreeItem*                  pTreeItem = static_cast<XTreeItem*>(pItem);
        bool                        bSelected = !pTreeItem->isSelected();
        CTraceServerPortal&         rPortal = CTraceClientApp::Instance().TraceServerPortal();

        NYXTRACE(0x0, L"onItemDoubleClicked : " << Nyx::CTF_Int(pTreeItem->device().id()) );

        if (bSelected)
            rPortal.setClientMapping( pTreeItem->device().id(), CTraceClientApp::Instance().AppSettings().clientId() );
        else
            rPortal.removeClientMapping( pTreeItem->device().id() );
    }
}


void CDevicesSelectionPanel::onDeviceAdded(const CDevice &device)
{
    addDevice(device);
}


void CDevicesSelectionPanel::onDeviceRemoved(const CDevice &device)
{

}


void CDevicesSelectionPanel::onDeviceMapped(int id)
{
    NYXTRACE(0x0, L"onDeviceMapped : " << Nyx::CTF_Int(id));

    int count = ui->devicesList->topLevelItemCount();
    int index = 0;

    while ( index < count )
    {
        XTreeItem* pItem = static_cast<XTreeItem*>(ui->devicesList->topLevelItem(index));

        if ( pItem->device().id() == id )
            pItem->setSelected(true);

        ++ index;
    }

    ui->devicesList->update();
}


void CDevicesSelectionPanel::onDeviceUnmapped(int id)
{
    NYXTRACE(0x0, L"onDeviceUnmapped : " << Nyx::CTF_Int(id));

    int count = ui->devicesList->topLevelItemCount();
    int index = 0;

    while ( index < count )
    {
        XTreeItem* pItem = static_cast<XTreeItem*>(ui->devicesList->topLevelItem(index));

        if ( pItem->device().id() == id )
            pItem->setSelected(false);

        ++ index;
    }

    ui->devicesList->update();
}




void CDevicesSelectionPanel::showEvent(QShowEvent *)
{
    QApplication*           app = static_cast<QApplication*>(QApplication::instance());
    CDevicesMgr&            rDevicesMgr = CTraceClientApp::Instance().DevicesMgr();
    CTraceServerPortal&     rPortal = CTraceClientApp::Instance().TraceServerPortal();

    listDevices();

    connect(    &rDevicesMgr, SIGNAL(deviceAdded(CDevice)),
                this, SLOT(onDeviceAdded(CDevice)));
    connect(    app, SIGNAL(focusChanged(QWidget*,QWidget*)),
                this, SLOT(onFocusChanged(QWidget*,QWidget*)) );
    connect(    &rPortal, SIGNAL(deviceMapped(int)),
                this, SLOT(onDeviceMapped(int)) );
    connect(    &rPortal, SIGNAL(deviceUnmapped(int)),
                this, SLOT(onDeviceUnmapped(int)) );

    CTraceClientApp::Instance().TraceServerPortal().getDevices();

    QCoreApplication* pApp = QApplication::instance();
    pApp->installEventFilter(this);
}


void CDevicesSelectionPanel::hideEvent(QHideEvent *)
{
    QCoreApplication* pApp = QApplication::instance();
    pApp->removeEventFilter(this);

    QApplication*   app = static_cast<QApplication*>(QApplication::instance());
    CDevicesMgr&    rDevicesMgr = CTraceClientApp::Instance().DevicesMgr();
    CTraceServerPortal&     rPortal = CTraceClientApp::Instance().TraceServerPortal();

    disconnect( app, SIGNAL(focusChanged(QWidget*,QWidget*)),
                this, SLOT(onFocusChanged(QWidget*,QWidget*)) );
    disconnect( &rDevicesMgr, SIGNAL(deviceAdded(CDevice)),
                this, SLOT(onDeviceAdded(CDevice)) );
    disconnect( &rPortal, SIGNAL(deviceMapped(int)),
                this, SLOT(onDeviceMapped(int)) );
    disconnect( &rPortal, SIGNAL(deviceUnmapped(int)),
                this, SLOT(onDeviceUnmapped(int)) );

    ui->devicesList->clear();
}


void CDevicesSelectionPanel::listDevices()
{
    CDevicesMgr&        rDevicesMgr = CTraceClientApp::Instance().DevicesMgr();
    CDevice::IdSet  set;
    CDevice::IdSet::const_iterator  pos;

    rDevicesMgr.listDevices(set);

    pos = set.begin();
    while (pos != set.end())
    {
        addDevice( rDevicesMgr.getDevice(*pos) );
        ++ pos;
    }
}


void CDevicesSelectionPanel::addDevice(const CDevice &device)
{
    CDevicesMapping&    rDevicesMapping = CTraceClientApp::Instance().devicesMapping();

    XTreeItem* pItem = new XTreeItem(device);
    ui->devicesList->addTopLevelItem(pItem);

    if ( rDevicesMapping.isDeviceMapped(device.id()) )
    {
        pItem->setSelected(true);
    }
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

