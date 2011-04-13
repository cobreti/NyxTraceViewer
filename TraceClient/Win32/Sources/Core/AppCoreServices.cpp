#include "AppCoreServices.hpp"


/**
 *
 */
CAppCoreServices* CAppCoreServices::s_pInstance = NULL;


/**
 *
 */
CAppCoreServices& CAppCoreServices::Instance()
{
	return *s_pInstance;
}


/**
 *
 */
CAppCoreServices::CAppCoreServices()
{
	s_pInstance = this;
}


/**
 *
 */
CAppCoreServices::~CAppCoreServices()
{
	s_pInstance = NULL;
}


/**
 *
 */
Nyx::NyxResult CAppCoreServices::Init()
{
	return Nyx::kNyxRes_Success;
}


/**
 *
 */
Nyx::NyxResult CAppCoreServices::Terminate()
{
	Feeders().Clear();

	return Nyx::kNyxRes_Success;
}
