#include "FeederSettings.hpp"


/**
 *
 */
CFeederSettings::CFeederSettings() :
m_ApiType(eTAPI_Nyx),
m_TracesPerBlock(100),
m_IntervalBetweenBlocks(1000)
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
m_IntervalBetweenBlocks(settings.m_IntervalBetweenBlocks)
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
    }

    return *this;
}
