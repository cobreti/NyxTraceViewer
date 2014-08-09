#ifndef CSTATICHIGHLIGHTS_HPP
#define CSTATICHIGHLIGHTS_HPP

#include "../TraceSectionId.h"
#include "ViewTraceSectionHilight.h"
#include "View/ViewTracesDisplayCache.h"

#include <map>
#include <QPainter>



class CStaticHighlights
{
public:
    CStaticHighlights();
    virtual ~CStaticHighlights();

    void Set( const CTraceSectionId& id, CViewTraceSectionHilight* pHighlight );
    void Remove( const CTraceSectionId& id );
    void Clear();

    void Draw( QPainter& painter, const CViewTracesDisplayCache& displayCache );

    const CStaticHighlights& operator += (const CStaticHighlights& highlights);

protected:

    void DrawItem( QPainter& painter, const CViewTracesDisplayCache::CEntryData& data, CViewTraceSectionHilight* pHilight );

protected:

    typedef     std::map<CTraceSectionId, CViewTraceSectionHilightRef>        THighlightsTable;

protected:

    THighlightsTable        m_highlights;
};

#endif // CSTATICHIGHLIGHTS_HPP
