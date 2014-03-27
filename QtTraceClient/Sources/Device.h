#ifndef DEVICE_H
#define DEVICE_H


#include <QtCore>
#include <list>


/**
 * @brief The CDevice class
 */
class CDevice
{
public:
    CDevice(const QString& name);
    virtual ~CDevice();

    const QString&      name() const        { return m_Name; }

protected:

    QString     m_Name;
};



/**
 * @brief The CDevicesList class
 */
class CDevicesList : public std::list<CDevice*>
{
public:
    CDevicesList() {}
    virtual ~CDevicesList() {}
};


#endif // DEVICE_H
