#ifndef _VIEWSETTINGS_HPP_
#define _VIEWSETTINGS_HPP_

#include "ViewItemsSettings.hpp"
#include "ViewColumnsSettings.hpp"
#include "ViewDrawSettings.hpp"

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

    CViewDrawSettings*      DrawSettings() const            { return m_pDrawSettings; }
    CViewDrawSettings*&     DrawSettings()                  { return m_pDrawSettings; }

    void UpdateFrom( const CViewSettings& settings );

    const CViewSettings& operator = (const CViewSettings& settings);

protected:

    CViewItemsSettings          m_ViewItemsSettings;
    CViewColumnsSettings        m_ViewColumnsSettings;
    CViewDrawSettings*          m_pDrawSettings;
    bool                        m_bDirty;
};



#endif // _VIEWSETTINGS_HPP_
