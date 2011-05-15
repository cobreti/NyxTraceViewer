#include <Nyx.hpp>

#include "TraceClientCoreModule.hpp"
#include "PoolsUpdateClock.hpp"

namespace TraceClientCore
{
    /**
     *
     */
    CModule* CModule::s_pInstance = NULL;


    /**
     *
     */
   CModule& CModule::Instance()
    {
	    return *s_pInstance;
    }


    /**
     *
     */
    CModule::CModule() :
    m_pPoolsUpdateClock(NULL)
    {
	    s_pInstance = this;
        m_pPoolsUpdateClock = new CPoolsUpdateClock();
    }


    /**
     *
     */
    CModule::~CModule()
    {
        delete m_pPoolsUpdateClock;
	    s_pInstance = NULL;
    }
}
