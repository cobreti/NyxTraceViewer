#include <Nyx.hpp>

#include "TraceClientCoreModule.hpp"


/**
 *
 */
TraceClientCore::CModule* TraceClientCore::CModule::s_pInstance = NULL;


/**
 *
 */
TraceClientCore::CModule& TraceClientCore::CModule::Instance()
{
	return *s_pInstance;
}


/**
 *
 */
TraceClientCore::CModule::CModule()
{
	s_pInstance = this;
}


/**
 *
 */
TraceClientCore::CModule::~CModule()
{
	s_pInstance = NULL;
}
