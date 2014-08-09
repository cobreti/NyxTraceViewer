#include "StaticHighlights.hpp"


CStaticHighlights::CStaticHighlights()
{
}


CStaticHighlights::~CStaticHighlights()
{
}


void CStaticHighlights::Set(const CTraceSectionId &id, CViewTraceSectionHilight *pHighlight)
{
    m_highlights[id] = pHighlight;
}


void CStaticHighlights::Remove(const CTraceSectionId &id)
{
    m_highlights.erase(id);
}


void CStaticHighlights::Clear()
{
    m_highlights.clear();
}


void CStaticHighlights::Draw(QPainter &painter, const CViewTracesDisplayCache &displayCache)
{
    auto forId = [&] (const CTraceSectionId& id, const CViewTracesDisplayCache::CEntryData data)
    {
        if ( m_highlights.count(id) > 0 )
            DrawItem(painter, data, m_highlights[id]);
    };

    displayCache.for_each(forId);
}


const CStaticHighlights& CStaticHighlights::operator += (const CStaticHighlights& highlights)
{
    auto foreachFct = [&] ( std::pair<const CTraceSectionId, const CViewTraceSectionHilightRef> pair )
    {
         m_highlights[pair.first] = pair.second;
    };

    std::for_each( highlights.m_highlights.begin(), highlights.m_highlights.end(), foreachFct );

    return *this;
}


void CStaticHighlights::DrawItem( QPainter& painter, const CViewTracesDisplayCache::CEntryData& data, CViewTraceSectionHilight* pHilight )
{
    pHilight->Draw(painter, data.itemArea());
}


