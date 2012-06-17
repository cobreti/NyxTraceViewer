#ifndef _VIEWITEMHIGHLIGHTER_SEARCHEDLINE_HPP_
#define _VIEWITEMHIGHLIGHTER_SEARCHEDLINE_HPP_


#include "View/Highlight/ViewItemHighlighter.hpp"


class CViewSearchEngine;


DECLARE_OBJECTREF(CViewItemHighlighter_SearchedLine)


/**
 *
 */
class CViewItemHighlighter_SearchedLine : public CViewItemHighlighter
{
public:
    CViewItemHighlighter_SearchedLine( CViewSearchEngine* pEngine );
    virtual ~CViewItemHighlighter_SearchedLine();

    virtual void OnPreItemDisplay(  const CViewSettings& rViewSettings,
                                    const CViewColumnSettings& rColumnSettings,
                                    CDrawViewItemState& rState,
                                    QFontMetricsF& rMetrics,
                                    const QString& text );

protected:

    CViewSearchEngine*          m_pSearchEngine;
};



#endif // _VIEWITEMHIGHLIGHTER_SEARCHEDLINE_HPP_

