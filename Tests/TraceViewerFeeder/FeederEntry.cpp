#include "FeederEntry.hpp"
#include "FeederBase.hpp"
#include "NyxFeeder.hpp"
#include "ExternalFeeder.hpp"

#if defined(_WIN32)
    #include "DllFeeder.hpp"
#endif

/**
 *
 */
CFeederEntry::CFeederEntry() :
m_pFeeder(NULL)
{
}


/**
 *
 */
CFeederEntry::~CFeederEntry()
{
}


/**
 *
 */
void CFeederEntry::Start()
{
    switch ( Settings().ApiType() )
    {
    case CFeederSettings::eTAPI_External:
        m_pFeeder = new CExternalFeeder();
        break;
#if defined(WIN32)
    case CFeederSettings::eTAPI_Dll:
        m_pFeeder = new CDllFeeder();
        break;
#endif
    case CFeederSettings::eTAPI_NyxPipe:
    case CFeederSettings::eTAPI_NyxTcpIp:
        m_pFeeder = new CNyxFeeder();
        break;
    };

    m_pFeeder->Start(m_Settings);
}


/**
 *
 */
void CFeederEntry::Stop()
{
    m_pFeeder->Stop();
    delete m_pFeeder;
    m_pFeeder = NULL;
}


/**
 *
 */
bool CFeederEntry::IsRunning() const
{
    if ( m_pFeeder )
        return m_pFeeder->IsRunning();

    return false;
}
