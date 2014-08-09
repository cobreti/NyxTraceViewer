#ifndef DEVICESMGR_H
#define DEVICESMGR_H

#include <QtCore>
#include <map>

#include "Device.h"



/**
 * @brief The CDevicesMgr class
 */
class CDevicesMgr : public QObject
{
    Q_OBJECT

public:
    CDevicesMgr();
    virtual ~CDevicesMgr();

    const CDevice& getDevice(int id);
    void listDevices( CDevice::IdSet& set );

public slots:

    void onDevicesRefreshed(const CDevice::IdMap& devicesList);

signals:

    void deviceAdded(const CDevice& device);
    void deviceRemoved(const CDevice& device);

protected:


protected:

    CDevice::IdMap          m_Devices;
};

#endif // DEVICESMGR_H

