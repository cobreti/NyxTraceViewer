#ifndef _VIEWITEMPATTERN_TEXT_HPP_
#define _VIEWITEMPATTERN_TEXT_HPP_

#include "View/Highlight/ViewItemPattern.hpp"
#include "View/Highlight/ViewItemPattern_Text.hpp"


DECLARE_OBJECTREF(CViewItemPattern_Text)

/**
 *
 */
class CViewItemPattern_Text : public CViewItemPattern
{
public:
    CViewItemPattern_Text();

    virtual Nyx::CRange Match( const QString& text,  const long& startIndex );
    virtual int PatternLength() const;

    const QString&  TextToMatch() const     { return m_TextToMatch; }
    QString&        TextToMatch()           { return m_TextToMatch; }

protected:
    virtual ~CViewItemPattern_Text();

protected:

    QString     m_TextToMatch;
};


#endif // _VIEWITEMPATTERN_TEXT_HPP_
