#ifndef APPSETTINGS_HPP
#define APPSETTINGS_HPP

#include <Nyx.hpp>
#include <map>

#include "View/ViewDrawSettings.hpp"

/**
 *
 */
class CAppSettings
{
public:
    CAppSettings();
    ~CAppSettings();

    const CViewDrawSettings& DefaultDrawSettings() const            { return m_DefaultViewDrawSettings; }
    CViewDrawSettings& DefaultDrawSettings()                        { return m_DefaultViewDrawSettings; }

protected:

    typedef     std::map<Nyx::CWString, CViewDrawSettings*>     TViewDrawSettingsTable;

protected:

    TViewDrawSettingsTable          m_ViewDrawSettings;
    CViewDrawSettings               m_DefaultViewDrawSettings;

};

#endif // APPSETTINGS_HPP
