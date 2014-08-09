#ifndef DEVICE_H
#define DEVICE_H


#include <QtCore>
//#include <list>

#include <map>
#include <set>


/**
 * @brief The CDevice class
 */
class CDevice
{
public:
    typedef     std::map<int, CDevice>      IdMap;
    typedef     std::set<int>               IdSet;

public:
    CDevice();
    CDevice(const CDevice& device);
    virtual ~CDevice();

    const QString&      name() const        { return m_Name; }
    QString&            name()              { return m_Name; }

    const QString&      alias() const       { return m_Alias; }
    QString&            alias()             { return m_Alias; }

    const int&          id() const          { return m_Id; }
    int&                id()                { return m_Id; }

    const CDevice& operator = (const CDevice& device);

protected:

    QString     m_Name;
    QString     m_Alias;
    int         m_Id;
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
