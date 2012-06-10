#ifndef _VIEWITEMHIGHLIGHTERSSET_HPP_
#define _VIEWITEMHIGHLIGHTERSSET_HPP_

#include "View/Highlight/ViewItemHighlighter.hpp"


DECLARE_OBJECTREF(CViewItemHighlightersSet)


/**
 *
 */
class CViewItemHighlightersSet : public CViewItemHighlighter
{
public:
    CViewItemHighlightersSet();

    virtual void Add( CViewItemHighlighter* pHighlighter );
    virtual void Remove( CViewItemHighlighter* pHighlighter );

    virtual void OnPreItemDisplay(  const CViewSettings& rViewSettings,
                                    const CViewColumnSettings& rColumnSettings,
                                    CDrawViewItemState& rState,
                                    QFontMetricsF& rMetrics,
                                    const QString& text );

    virtual void OnPostItemDisplay( const CViewSettings& rViewSettings,
                                    const CViewColumnSettings& rColumnSettings,
                                    CDrawViewItemState& rState,
                                    QFontMetricsF& rMetrics,
                                    const QString& text );

protected:
    virtual ~CViewItemHighlightersSet();

protected:

    ViewItemHighlightersList                m_Children;
};


#endif // _VIEWITEMHIGHLIGHTERSSET_HPP_
