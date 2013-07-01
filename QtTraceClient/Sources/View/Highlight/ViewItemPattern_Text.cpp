#include "View/Highlight/ViewItemPattern_Text.hpp"


/**
 *
 */
CViewItemPattern_Text::CViewItemPattern_Text() : CViewItemPattern()
{
}


/**
 *
 */
Nyx::CRange CViewItemPattern_Text::Match( const QString& text, const long& startIndex )
{
    if ( m_TextToMatch.isEmpty() )
        return Nyx::CRange();

    Nyx::CRange     res;

    res.Start() = text.indexOf(m_TextToMatch, startIndex, Qt::CaseInsensitive);
    if ( res.Start() > -1 )
        res.Length() = m_TextToMatch.length();

    return res;
}


/**
 *
 */
int CViewItemPattern_Text::PatternLength() const
{
    return m_TextToMatch.length();
}


/**
 *
 */
CViewItemPattern_Text::~CViewItemPattern_Text()
{
}


