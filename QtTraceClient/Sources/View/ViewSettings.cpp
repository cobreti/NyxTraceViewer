#include "ViewSettings.hpp"

/**
 *
 */
CViewSettings::CViewSettings() :
    m_pDrawSettings(NULL),
    m_bDirty(false),
    m_SelectionColor(Qt::yellow),
    m_SelectionBorderColor(Qt::darkYellow)
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


/**
 *
 */
const CViewSettings& CViewSettings::operator = (const CViewSettings& settings)
{
    if ( this != &settings )
    {
        m_ViewItemsSettings = settings.m_ViewItemsSettings;
        m_ViewColumnsSettings = settings.m_ViewColumnsSettings;
        m_SelectionColor = settings.m_SelectionColor;
        m_SelectionBorderColor = settings.m_SelectionBorderColor;
    }

    return *this;
}

