#include "ViewSettings.hpp"


/**
 *
 */
CViewSettings::CViewSettings() :
m_bDirty(false)
{
}


/**
 *
 */
CViewSettings::~CViewSettings()
{
}


/**
 *
 */
void CViewSettings::UpdateFrom(const CViewSettings &settings)
{
    m_ViewColumnsSettings.UpdateFrom(settings.ColumnsSettings());
}

