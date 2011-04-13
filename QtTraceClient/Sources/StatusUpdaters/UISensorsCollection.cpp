#include "UISensorsCollection.hpp"
#include "UISensor.hpp"


/**
 *
 */
CUISensorsCollection::CUISensorsCollection()
{
}


/**
 *
 */
CUISensorsCollection::~CUISensorsCollection()
{
	Clear();
}


/**
 *
 */
void CUISensorsCollection::Add(CUISensor* pSensor)
{
	m_Sensors.push_back( pSensor );
}


/**
 *
 */
void CUISensorsCollection::Clear()
{
	while ( !m_Sensors.empty() )
	{
		delete m_Sensors.front();
		m_Sensors.pop_front();
	}
}


