#ifndef APPSETTINGS_HPP
#define APPSETTINGS_HPP

#include <Nyx.hpp>
#include <map>

#include "View/ViewDrawSettings.hpp"
#include "View/ViewSettings.hpp"
#include "View/Highlight/ViewHighlightSettings.hpp"


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

    const CViewHighlightSettings&       ViewHighlightSettings() const       { return m_HighlightSettings; }
    CViewHighlightSettings&             ViewHighlightSettings()             { return m_HighlightSettings; }

    const int&      clientId() const            { return m_ClientId; }
    int&            clientId()                  { return m_ClientId; }


protected:

    typedef     std::map<Nyx::CWString, CViewDrawSettings*>     TViewDrawSettingsTable;

protected:

    void Init();

protected:

    TViewDrawSettingsTable          m_ViewDrawSettings;
    CViewDrawSettings               m_DefaultViewDrawSettings;
    CViewSettings                   m_DefaultViewSettings;
    CViewHighlightSettings          m_HighlightSettings;
    int                             m_ClientId;

};

#endif // APPSETTINGS_HPP
