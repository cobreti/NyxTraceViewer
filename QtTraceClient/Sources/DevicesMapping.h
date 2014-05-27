#ifndef DEVICESMAPPING_H
#define DEVICESMAPPING_H

#include "Device.h"

#include <QObject>


class CDevicesMapping : public QObject
{
    Q_OBJECT

public:
    CDevicesMapping();
    virtual ~CDevicesMapping();

    void Init();
    bool isDeviceMapped(int id) const;

public slots:

    void onClientMapping(int id, const QString& alias, const QString& name);
    void onDeviceMapped(int id);
    void onDeviceUnmapped(int id);

signals:

    void addedDevice(int id);
    void removedDevice(int id);

protected:


protected:

    CDevice::IdSet        m_MappedDevices;
};


#endif // DEVICESMAPPING_H
