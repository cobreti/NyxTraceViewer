#include "StatusUpdaters/UISensor.hpp"
#include "StatusUpdaters/StatusUpdater.hpp"


/**
 *
 */
CUISensor::CUISensor(void*, const CStatusUpdater& rStatusUpdater) : m_rStatusUpdater(rStatusUpdater)
{
}


/**
 *
 */
CUISensor::~CUISensor()
{
}


/**
 *
 */
void CUISensor::SendUpdate()
{
	m_rStatusUpdater.OnUpdate();
}
