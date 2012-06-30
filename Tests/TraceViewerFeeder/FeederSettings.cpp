#include "FeederSettings.hpp"


/**
 *
 */
CFeederSettings::CFeederSettings() :
    m_ApiType(eTAPI_NyxPipe),
    m_TracesPerBlock(1),
    m_IntervalBetweenBlocks(1000),
    m_pFeederSource(NULL)
{
}


/**
 *
 */
CFeederSettings::CFeederSettings(const CFeederSettings& settings) :
    m_Name(settings.m_Name),
    m_Text(settings.m_Text),
    m_ApiType(settings.m_ApiType),
    m_TracesPerBlock(settings.m_TracesPerBlock),
    m_IntervalBetweenBlocks(settings.m_IntervalBetweenBlocks),
    m_pFeederSource(settings.m_pFeederSource)
{
}


/**
 *
 */
CFeederSettings::~CFeederSettings()
{
}


/**
 *
 */
const CFeederSettings& CFeederSettings::operator = (const CFeederSettings& settings)
{
    if ( this != &settings )
    {
        m_Name = settings.m_Name;
        m_Text = settings.m_Text;
        m_ApiType = settings.m_ApiType;
        m_TracesPerBlock = settings.m_TracesPerBlock;
        m_IntervalBetweenBlocks = settings.m_IntervalBetweenBlocks;
        m_pFeederSource = settings.m_pFeederSource;
    }

    return *this;
}
