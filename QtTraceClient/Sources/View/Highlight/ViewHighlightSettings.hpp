#ifndef _VIEWHIGHLIGHTSETTINGS_HPP_
#define _VIEWHIGHLIGHTSETTINGS_HPP_

#include "HighlightBrushesSet.hpp"

/**
 *
 */
class CViewHighlightSettings
{
public:
    CViewHighlightSettings();
    virtual ~CViewHighlightSettings();

    const CHighlightBrushesSet&         WordHighlights() const     { return m_WordHighlights; }
    CHighlightBrushesSet&               WordHighlights()           { return m_WordHighlights; }

    const CHighlightBrushesSet&         LineHighlights() const     { return m_LineHighlights; }
    CHighlightBrushesSet&               LineHighlights()           { return m_LineHighlights; }

protected:

    CHighlightBrushesSet        m_WordHighlights;
    CHighlightBrushesSet        m_LineHighlights;
};


#endif // _VIEWHIGHLIGHTSETTINGS_HPP_
