#include "DynamicHighlightsDirectory.h"



CDynamicHighlightsDirectory::CDynamicHighlightsDirectory()
{

}


CDynamicHighlightsDirectory::~CDynamicHighlightsDirectory()
{
    auto    cleanFct = [] ( std::pair<const CDynamicHighlight::ID, const CDynamicHighlight*> pair ) { delete pair.second; };

    std::for_each( m_Highlights.begin(), m_Highlights.end(), cleanFct );
}


void CDynamicHighlightsDirectory::Add(CDynamicHighlight *pHighlight)
{
    CDynamicHighlight*  pExistingHighlight = NULL;
    HighlightsTable::iterator pos = m_Highlights.find(pHighlight->id());

    if ( pos != m_Highlights.end() )
    {
        pExistingHighlight = pos->second;
        m_Highlights.erase(pos);

        if ( pExistingHighlight != pHighlight )
            delete pExistingHighlight;
    }

    m_Highlights.insert( std::make_pair(pHighlight->id(), pHighlight) );
}


void CDynamicHighlightsDirectory::Remove(const CDynamicHighlight::ID &id)
{
    CDynamicHighlight*  pExistingHighlight = NULL;
    HighlightsTable::iterator pos = m_Highlights.find(id);

    if ( pos != m_Highlights.end() )
    {
        pExistingHighlight = pos->second;
        m_Highlights.erase(pos);
        delete pExistingHighlight;
    }
}


CDynamicHighlight* CDynamicHighlightsDirectory::Get( const CDynamicHighlight::ID& id )
{
    HighlightsTable::iterator pos = m_Highlights.find(id);
    if ( pos != m_Highlights.end() )
        return pos->second;

    return NULL;
}


void CDynamicHighlightsDirectory::Draw( CViewTracePainter::CPaintContext& context ) const
{
    auto    drawFct = [&] ( std::pair<const CDynamicHighlight::ID, CDynamicHighlight*> pair )
    {
        pair.second->Draw(context);
    };

    std::for_each( m_Highlights.begin(), m_Highlights.end(), drawFct );

}
