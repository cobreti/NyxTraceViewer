
#include "DevicesSelectionPanel.h"
#include "TraceClientApp.h"
#include "DevicesMgr.h"

#include "ui_DevicesSelection.h"

#include <QApplication>


/**
 * @brief CDevicesSelection::CDevicesSelection
 */
CDevicesSelectionPanel::CDevicesSelectionPanel() : QWidget(),
    ui(new Ui::DevicesSelection())
{
    ui->setupUi(this);

    ui->removeDeviceBtn->setEnabled(false);
    ui->addDeviceBtn->setEnabled(false);

    connect( ui->deviceNameEdit, SIGNAL(textChanged(QString)), this, SLOT(onDeviceNameChanged(QString)));
    connect( ui->addDeviceBtn, SIGNAL(clicked()), this, SLOT(onAddDevice()));
}


/**
 * @brief CDevicesSelection::~CDevicesSelection
 */
CDevicesSelectionPanel::~CDevicesSelectionPanel()
{

}


/**
 * @brief CDevicesSelectionPanel::onDeviceNameChanged
 * @param text
 */
void CDevicesSelectionPanel::onDeviceNameChanged(const QString &text)
{
    CDevicesMgr&    rDevicesMgr = CTraceClientApp::Instance().DevicesMgr();
    bool            bAddEnabled = !text.isEmpty() && !rDevicesMgr.IsDeviceWithNameExists(text);

    ui->addDeviceBtn->setEnabled(bAddEnabled);
}


void CDevicesSelectionPanel::onAddDevice()
{
    CDevicesMgr&    rDevicesMgr = CTraceClientApp::Instance().DevicesMgr();
    QString         deviceName = ui->deviceNameEdit->text();
    CDevice*        pDevice = new CDevice(deviceName);

    rDevicesMgr.AddDevice(pDevice);
    ui->addDeviceBtn->setEnabled(false);
    ui->deviceList->addItem(deviceName);
}


void CDevicesSelectionPanel::onFocusChanged(QWidget *pOld, QWidget *pNew)
{
}


void CDevicesSelectionPanel::showEvent(QShowEvent *)
{
    QApplication*   app = static_cast<QApplication*>(QApplication::instance());

    connect( app, SIGNAL(focusChanged(QWidget*,QWidget*)), this, SLOT(onFocusChanged(QWidget*,QWidget*)) );
}


void CDevicesSelectionPanel::hideEvent(QHideEvent *)
{
    QApplication*   app = static_cast<QApplication*>(QApplication::instance());

    disconnect( app, SIGNAL(focusChanged(QWidget*,QWidget*)), this, SLOT(onFocusChanged(QWidget*,QWidget*)) );
}
