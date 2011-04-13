#ifndef _UISENSORSCOLLECTION_HPP_
#define _UISENSORSCOLLECTION_HPP_

#include <list>

class CUISensor;


class CUISensorsCollection
{
public:
	CUISensorsCollection();
	virtual ~CUISensorsCollection();

	virtual void Add( CUISensor* pSensor );
	virtual void Clear();

protected: // protected types

	typedef		std::list<CUISensor*>		SensorsList;

protected: // protected members

	SensorsList		m_Sensors;
};


#endif // _UISENSORSCOLLECTION_HPP_
