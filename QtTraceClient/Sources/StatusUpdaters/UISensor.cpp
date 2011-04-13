#include "StatusUpdaters/UISensor.hpp"
#include "StatusUpdaters/StatusUpdater.hpp"


/**
 *
 */
CUISensor::CUISensor(void* pCtrl, const CStatusUpdater& rStatusUpdater) : m_rStatusUpdater(rStatusUpdater)
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
