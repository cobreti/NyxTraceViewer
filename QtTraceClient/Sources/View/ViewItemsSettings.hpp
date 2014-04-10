#ifndef VIEWITEMSSETTINGS_HPP
#define VIEWITEMSSETTINGS_HPP

#include "ViewItemSettings.hpp"

#include <map>


/**
 *
 */
class CViewItemsSettings
{
public:
    CViewItemsSettings();
    virtual ~CViewItemsSettings();

    virtual void SetDefault(CViewItemSettings* pSetting)         { m_refDefault = pSetting; }
    virtual CViewItemSettings* GetDefault() const                { return m_refDefault; }

	const CViewItemsSettings& operator = (const CViewItemsSettings& settings);

protected:

protected:

    CViewItemSettingsRef    m_refDefault;
};

#endif // VIEWITEMSSETTINGS_HPP
