#ifndef _VIEWSEARCHENGINE_H_
#define _VIEWSEARCHENGINE_H_

#include "View/Highlight/ViewItemPattern_Text.hpp"
#include "View/highlight/ViewItemHighlighter.hpp"
#include "View/highlight/ViewItemHighlighter_SearchedLine.hpp"


class CTracesView;

/**
 *
 */
class CViewSearchEngine
{
public:

    /**
     *
     */
    class XFindPos
    {
    public:
        XFindPos() : m_bValid(false) {}
        ~XFindPos() {}

        operator bool() const { return m_bValid; }

        const XFindPos& operator = (const XFindPos& pos)
        {
            m_bValid = pos.m_bValid;
            m_LineNumber = pos.m_LineNumber;

            return *this;
        }

        const XFindPos& operator = (const size_t LineNumber)
        {
            m_LineNumber = LineNumber;
            m_bValid = true;

            return *this;
        }


        const size_t LineNumber() const     { return m_LineNumber; }



    protected:

        size_t      m_LineNumber;
        bool        m_bValid;
    };

public:
    CViewSearchEngine(CTracesView& rView);
    virtual ~CViewSearchEngine();

    const CViewItemHighlighterRef   Highlighter() const             { return m_refHighlighter; }
    CViewItemHighlighterRef&         Highlighter()                  { return m_refHighlighter; }

    const XFindPos&     FoundPos() const            { return m_FoundPos; }

    //void SetText(const QString& text);

    void Next();
    void Previous();

    CTracesView&    View()      { return m_rView; }

protected:

    CTracesView&                            m_rView;
    XFindPos                                m_FoundPos;

    //CViewItemPattern_TextRef                m_refSearchPattern;
    CViewItemHighlighterRef                 m_refHighlighter;

    CViewItemHighlighter_SearchedLineRef    m_refSearchedLineHighlighter;

};


#endif // _VIEWSEARCHENGINE_HPP_
