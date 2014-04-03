#include "Device.h"


CDevice::CDevice() :
    m_Id(-1)
{

}


CDevice::CDevice(const CDevice &device) :
    m_Name(device.m_Name),
    m_Alias(device.m_Alias),
    m_Id(device.m_Id)
{

}


CDevice::~CDevice()
{

}


const CDevice& CDevice::operator = (const CDevice& device)
{
    m_Name = device.m_Name;
    m_Alias = device.m_Alias;
    m_Id = device.m_Id;

    return *this;
}
