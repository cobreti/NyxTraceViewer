#include "ViewItemsSettings.hpp"


/**
 *
 */
CViewItemsSettings::CViewItemsSettings()
{
    m_refDefault = new CViewItemSettings();
}


/**
 *
 */
CViewItemsSettings::~CViewItemsSettings()
{
}


/**
 *
 */
void CViewItemsSettings::Add(CViewItemPainter::EPainterId id, CViewItemSettings *pSetting)
{
    m_Settings[id] = pSetting;
}


/**
 *
 */
CViewItemSettings* CViewItemsSettings::operator [] (const CViewItemPainter::EPainterId& id) const
{
    SettingsMap::const_iterator     pos = m_Settings.find(id);

    if ( pos == m_Settings.end() )
        return m_refDefault;

    return pos->second;
}


/**
 *
 */
const CViewItemsSettings& CViewItemsSettings::operator = (const CViewItemsSettings& settings)
{
	SettingsMap::const_iterator			srcPos;
	SettingsMap::iterator				dstPos;

	for ( srcPos = settings.m_Settings.begin(); srcPos != settings.m_Settings.end(); ++srcPos )
	{
		dstPos = m_Settings.find(srcPos->first);
		if ( dstPos != m_Settings.end() )
			*dstPos->second = *srcPos->second;
		else
			m_Settings[srcPos->first] = srcPos->second->Clone();
	}

    m_refDefault = settings.m_refDefault->Clone();

	return *this;
}
