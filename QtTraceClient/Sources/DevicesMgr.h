#ifndef DEVICESMGR_H
#define DEVICESMGR_H

#include <QtCore>
#include <map>

#include "Device.h"



/**
 * @brief The CDevicesMgr class
 */
class CDevicesMgr : QObject
{
    Q_OBJECT

public:
    CDevicesMgr();
    virtual ~CDevicesMgr();

    bool AddDevice(CDevice* pDevice);
    bool IsDeviceWithNameExists(const QString name);

    void GetDevicesList( CDevicesList& list ) const;

public slots:

signals:

protected:

    typedef std::map<QString, CDevice*>      TDevicesMap;

protected:

    TDevicesMap     m_Devices;
};

#endif // DEVICESMGR_H

