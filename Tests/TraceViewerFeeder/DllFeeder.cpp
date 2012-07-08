#include "DllFeeder.hpp"
#include "NyxTraceViewerConnection.hpp"
#include "FeederSettings.hpp"

#include <Nyx.hpp>


/**
 *
 */
CDllFeeder::CDllFeeder() :
CFeederBase(),
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
    Nyx::NyxResult      res;

    m_refExternalModule = Nyx::CExternalModule::Alloc("DllFeed.dll");
    res = m_refExternalModule->Load();

    if ( Nyx::Succeeded(res) )
    {
        Nyx::CAString     name;
        name = Settings().Name();

//        CTraceClientLink::CreateDllInstance(m_refExternalModule->GetHandle(), name.c_str(), CTraceClientLink::eCT_WideChar);

        PFCTAllocDllFeedObject      pfctAlloc = (PFCTAllocDllFeedObject)m_refExternalModule->GetFct("AllocDllFeedObject");
        
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

    if ( m_refExternalModule->Valid() )
    {
//        CTraceClientLink::ReleaseDllInstance( m_refExternalModule->GetHandle() );
        m_refExternalModule->Unload();
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
