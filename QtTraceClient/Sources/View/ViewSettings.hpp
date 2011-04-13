#ifndef _VIEWSETTINGS_HPP_
#define _VIEWSETTINGS_HPP_

#include "ViewItemsSettings.hpp"
#include "ViewColumnsSettings.hpp"

/**
 *
 */
class CViewSettings
{
public:
    CViewSettings();
	virtual ~CViewSettings();

    const CViewItemsSettings&           ViewItemsSettings() const		{ return m_ViewItemsSettings; }
    CViewItemsSettings&                 ViewItemsSettings()				{ return m_ViewItemsSettings; }

    const CViewColumnsSettings&         ColumnsSettings() const			{ return m_ViewColumnsSettings; }
    CViewColumnsSettings&               ColumnsSettings()				{ return m_ViewColumnsSettings; }

    bool        Dirty() const       { return m_bDirty; }
    bool&       Dirty()             { return m_bDirty; }

    void UpdateFrom( const CViewSettings& settings );

protected:

    CViewItemsSettings          m_ViewItemsSettings;
    CViewColumnsSettings        m_ViewColumnsSettings;
    bool                        m_bDirty;
};



#endif // _VIEWSETTINGS_HPP_
