#include "StatusUpdaters/StatusUpdater.hpp"
#include "StatusUpdaters/UISensor_LineEdit.hpp"
#include "StatusUpdaters/UISensorsFactory.hpp"
#include "StatusUpdaters/UISensorCreator.hpp"

/**
 *
 */
CStatusUpdater::CStatusUpdater()
{
}


/**
 *
 */
CStatusUpdater::~CStatusUpdater()
{
}


/**
 *
 */
void CStatusUpdater::CreateSensorForCtrl( void* pCtrl, const char* className )
{
	CUISensorCreator*	pCreator = CUISensorsFactory::Instance().Get(className);

	if ( pCreator != NULL )
	{
		UISensors().Add( pCreator->CreateUISensor(pCtrl, *this) );
	}
	//if ( strcmp(QLineEdit().metaObject()->className(), className) == 0 )
	//{
	//	UISensors().Add( CUISensor_LineEdit(pCtrl, *this) );
	//}
}

