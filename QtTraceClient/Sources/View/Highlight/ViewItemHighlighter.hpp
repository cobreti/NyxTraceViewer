#ifndef _VIEWITEMHIGHLIGHTER_HPP_
#define _VIEWITEMHIGHLIGHTER_HPP_

#include <Nyx.hpp>
#include <list>

#include <QString>
#include <QFontMetricsF>
#include <QColor>

#include "View/Highlight/ViewItemPattern.hpp"


class CViewSettings;
class CDrawViewItemState;
class CViewColumnSettings;

DECLARE_OBJECTREF(CViewItemHighlighter);


typedef     std::list<CViewItemHighlighterRef>          ViewItemHighlightersList;


/**
 *
 */
class CViewItemHighlighter : public Nyx::CRefCount_Impl<>
{
public:
    CViewItemHighlighter();

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
                                    
    CViewItemPatternRef         Pattern() const         { return m_refPattern; }
    CViewItemPatternRef&        Pattern()               { return m_refPattern; }

    const QColor&   HighlightColor() const              { return m_HighlightColor; }
    QColor&         HighlightColor()                    { return m_HighlightColor; }

protected:
    virtual ~CViewItemHighlighter();

protected:

    CViewItemPatternRef     m_refPattern;
    QColor                  m_HighlightColor;
};


#endif // _VIEWITEMHIGHLIGHTER_HPP_
