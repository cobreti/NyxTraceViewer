#include "DevicesMgr.h"
#include "TraceClientApp.h"
#include "ServerAccess/TraceServerPortal.h"


/**
 * @brief CDevicesMgr::CDevicesMgr
 */
CDevicesMgr::CDevicesMgr()
{
    connect(    &CTraceClientApp::Instance().TraceServerPortal(), SIGNAL(devicesRefresh(CDevice::IdMap)),
                this, SLOT(onDevicesRefreshed(CDevice::IdMap)));
}


/**
 * @brief CDevicesMgr::~CDevicesMgr
 */
CDevicesMgr::~CDevicesMgr()
{

}

const CDevice& CDevicesMgr::getDevice(int id)
{
    return m_Devices[id];
}


void CDevicesMgr::listDevices(CDevice::IdSet &set)
{
    CDevice::IdMap::const_iterator  pos = m_Devices.begin();

    while (pos != m_Devices.end())
    {
        set.insert( pos->first );
        ++ pos;
    }
}


void CDevicesMgr::onDevicesRefreshed(const CDevice::IdMap &devicesList)
{
    CDevice::IdMap::const_iterator      pos;

    pos = devicesList.begin();
    while (pos != devicesList.end())
    {
        if ( m_Devices.count(pos->second.id()) == 0 ) // new device
        {
            m_Devices[pos->second.id()] = pos->second;
            CDevice device(pos->second);
            emit deviceAdded(device);
        }

        ++ pos;
    }

    pos = m_Devices.begin();
    while (pos != m_Devices.end())
    {
        if ( devicesList.count(pos->second.id()) == 0 ) // removed device
        {
            emit deviceRemoved(pos->second);
        }

        ++ pos;
    }
}

