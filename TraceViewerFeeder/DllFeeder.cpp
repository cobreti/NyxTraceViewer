#include "DllFeeder.hpp"
#include "TraceClientLink.hpp"
#include "FeederSettings.hpp"

#include <Nyx.hpp>


/**
 *
 */
CDllFeeder::CDllFeeder() :
CFeederBase(),
m_hDllInstance(NULL),
m_pFeedObject(NULL)
{
}


/**
 *
 */
CDllFeeder::~CDllFeeder()
{
}


/**
 *
 */
void CDllFeeder::OnBegin()
{
    m_hDllInstance = ::LoadLibraryA("DllFeed.dll");
    if ( m_hDllInstance )
    {
        Nyx::CAString     name;
        name = Settings().Name();

        CTraceClientLink::CreateDllInstance(m_hDllInstance, name.c_str(), CTraceClientLink::eCT_WideChar);

        PFCTAllocDllFeedObject      pfctAlloc = (PFCTAllocDllFeedObject)::GetProcAddress(m_hDllInstance, "AllocDllFeedObject");
        
        if (pfctAlloc)
            m_pFeedObject = pfctAlloc();
    }

    if ( m_pFeedObject )
        m_pFeedObject->Start();
}


/**
 *
 */
void CDllFeeder::OnEnd()
{
    if ( m_pFeedObject )
    {
        m_pFeedObject->Stop();
        delete m_pFeedObject;
        m_pFeedObject = NULL;
    }

    if ( m_hDllInstance )
    {
        CTraceClientLink::ReleaseDllInstance(m_hDllInstance);

        ::FreeLibrary(m_hDllInstance);
        m_hDllInstance = NULL;
    }
}


/**
 *
 */
void CDllFeeder::OnSendTrace()
{
    if ( m_pFeedObject )
        m_pFeedObject->SendTrace();
}
