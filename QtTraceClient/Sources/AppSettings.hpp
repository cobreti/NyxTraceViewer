#ifndef APPSETTINGS_HPP
#define APPSETTINGS_HPP

#include <Nyx.hpp>
#include <map>

#include "View/ViewDrawSettings.hpp"
#include "View/ViewSettings.hpp"

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

    const CViewSettings&        DefaultViewSettings() const         { return m_DefaultViewSettings; }

protected:

    typedef     std::map<Nyx::CWString, CViewDrawSettings*>     TViewDrawSettingsTable;

protected:

    void Init();

protected:

    TViewDrawSettingsTable          m_ViewDrawSettings;
    CViewDrawSettings               m_DefaultViewDrawSettings;
    CViewSettings                   m_DefaultViewSettings;

};

#endif // APPSETTINGS_HPP
