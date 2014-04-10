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
const CViewItemsSettings& CViewItemsSettings::operator = (const CViewItemsSettings& settings)
{
    m_refDefault = settings.m_refDefault->Clone();

	return *this;
}
