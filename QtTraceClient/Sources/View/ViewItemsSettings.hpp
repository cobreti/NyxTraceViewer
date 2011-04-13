#ifndef VIEWITEMSSETTINGS_HPP
#define VIEWITEMSSETTINGS_HPP

#include "ViewItemPainter.hpp"
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

    virtual void Add( CViewItemPainter::EPainterId id, CViewItemSettings* pSetting );

    CViewItemSettings* operator [] (const CViewItemPainter::EPainterId& id) const;

	const CViewItemsSettings& operator = (const CViewItemsSettings& settings);

protected:

    typedef     std::map<CViewItemPainter::EPainterId, CViewItemSettingsRef>     SettingsMap;

protected:

    SettingsMap             m_Settings;

    CViewItemSettingsRef    m_refDefault;
};

#endif // VIEWITEMSSETTINGS_HPP
