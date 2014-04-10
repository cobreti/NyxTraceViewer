#include "DevicesMapping.h"
#include "TraceClientApp.h"
#include "ServerAccess/TraceServerPortal.h"

CDevicesMapping::CDevicesMapping() : QObject()
{

}


CDevicesMapping::~CDevicesMapping()
{

}


void CDevicesMapping::Init()
{
    CTraceServerPortal& rServerPortal = CTraceClientApp::Instance().TraceServerPortal();

    connect(    &rServerPortal, SIGNAL(clientMapping(int,QString,QString)),
                this, SLOT(onClientMapping(int,QString,QString)) );

}


bool CDevicesMapping::isDeviceMapped(int id) const
{
    return m_MappedDevices.count(id) > 0;
}


void CDevicesMapping::onClientMapping(int id, const QString &alias, const QString &name)
{
    m_MappedDevices.insert(id);

    emit addedDevice(id);
}
