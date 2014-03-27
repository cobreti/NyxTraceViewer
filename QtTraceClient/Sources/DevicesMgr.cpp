#include "DevicesMgr.h"



/**
 * @brief CDevicesMgr::CDevicesMgr
 */
CDevicesMgr::CDevicesMgr()
{

}


/**
 * @brief CDevicesMgr::~CDevicesMgr
 */
CDevicesMgr::~CDevicesMgr()
{

}



bool CDevicesMgr::AddDevice(CDevice *pDevice)
{
    if ( NULL == pDevice )
        return false;

    if ( m_Devices.count(pDevice->name()) > 0 )
        return false;

    m_Devices[pDevice->name()] = pDevice;

    return true;
}


bool CDevicesMgr::IsDeviceWithNameExists(const QString name)
{
    return m_Devices.count(name) > 0;
}


void CDevicesMgr::GetDevicesList(CDevicesList &list) const
{
    TDevicesMap::const_iterator     pos = m_Devices.begin();

    list.clear();

    while ( pos != m_Devices.end() )
    {
        list.push_back(pos->second);
        ++ pos;
    }
}

