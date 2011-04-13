#include "ViewColumnsSettings.hpp"
#include "ViewColumnSettings.hpp"

/**
 *
 */
CViewColumnsSettings::CViewColumnsSettings() :
m_VisibleColumnsCount(eVCI_Count)
{
}


/**
 *
 */
CViewColumnsSettings::~CViewColumnsSettings()
{
	ColumnSettingsTable::iterator	pos;

	for (pos = m_Settings.begin(); pos != m_Settings.end(); ++pos)
		delete pos->second;
}


/**
 *
 */
void CViewColumnsSettings::Set( EViewColumnId ColumnId, CViewColumnSettings* pSettings )
{
	size_t count = m_Settings.count(ColumnId);

	if ( count > 0 )
	{
		ColumnSettingsTable::iterator	pos = m_Settings.find(ColumnId);

		if ( pSettings != pos->second )
		{
			delete pos->second;
			m_Settings.erase(pos);
		}
	}

	if ( pSettings )
		m_Settings[ColumnId] = pSettings;
}


/**
 *
 */
const CViewColumnSettings& CViewColumnsSettings::operator [] ( EViewColumnId id ) const
{
    ColumnSettingsTable::const_iterator pos = m_Settings.find(id);
    return *pos->second;
}


/**
 *
 */
CViewColumnSettings& CViewColumnsSettings::operator [] ( EViewColumnId id )
{
    return *(m_Settings[id]);
}


/**
 *
 */
qreal CViewColumnsSettings::GetTotalWidth() const
{
    qreal   width(0);

    ColumnSettingsTable::const_iterator pos;

    for (pos = m_Settings.begin(); pos != m_Settings.end(); ++pos)
        if ( pos->second->GetVisible() )
            width += pos->second->GetWidth();

    return width;
}


/**
 *
 */
void CViewColumnsSettings::UpdateFrom(const CViewColumnsSettings &settings)
{
    ColumnSettingsTable::const_iterator     SrcPos = settings.m_Settings.begin();

    while ( SrcPos != settings.m_Settings.end() )
    {
        ColumnSettingsTable::iterator       DstPos = m_Settings.find(SrcPos->first);

        if ( DstPos != m_Settings.end() )
        {
            if ( DstPos->second->AutoWidth() )
                DstPos->second->SetWidth( SrcPos->second->GetWidth() );
        }

        ++ SrcPos;
    }
}

