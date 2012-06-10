#include "View/Highlight/ViewItemHighlightersSet.hpp"


/**
 *
 */
CViewItemHighlightersSet::CViewItemHighlightersSet() : CViewItemHighlighter()
{
}


/**
 *
 */
void CViewItemHighlightersSet::Add( CViewItemHighlighter *pHighlighter )
{
    m_Children.push_back(pHighlighter);
}


/**
 *
 */
void CViewItemHighlightersSet::Remove( CViewItemHighlighter* pHighlighter )
{
    ViewItemHighlightersList::iterator      pos = m_Children.begin();

    while ( pos != m_Children.end() && (*pos) != pHighlighter )
        ++ pos;

    if ( pos != m_Children.end() )
        m_Children.erase(pos);
}


/**
 *
 */
void CViewItemHighlightersSet::OnPreItemDisplay(    const CViewSettings& rViewSettings,
                                                    const CViewColumnSettings& rColumnSettings,
                                                    CDrawViewItemState& rState,
                                                    QFontMetricsF& rMetrics,
                                                    const QString& text )
{
    ViewItemHighlightersList::iterator        pos  = m_Children.begin();

    while ( pos != m_Children.end() )
    {
        (*pos)->OnPreItemDisplay(rViewSettings, rColumnSettings, rState, rMetrics, text);
        ++ pos;
    }
}


/**
 *
 */
void CViewItemHighlightersSet::OnPostItemDisplay(   const CViewSettings& rViewSettings,
                                                    const CViewColumnSettings& rColumnSettings,
                                                    CDrawViewItemState& rState,
                                                    QFontMetricsF& rMetrics,
                                                    const QString& text )
{
    ViewItemHighlightersList::iterator        pos  = m_Children.begin();

    while ( pos != m_Children.end() )
    {
        (*pos)->OnPostItemDisplay(rViewSettings, rColumnSettings, rState, rMetrics, text);
        ++ pos;
    }
}


/**
 *
 */
CViewItemHighlightersSet::~CViewItemHighlightersSet()
{
}
