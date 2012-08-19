#ifndef _VIEWSEARCHENGINE_H_
#define _VIEWSEARCHENGINE_H_

#include "View/Highlight/ViewItemPattern_Text.hpp"
#include "View/Highlight/ViewItemHighlighter.hpp"
#include "View/Highlight/ViewItemHighlighter_SearchedLine.hpp"


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
            m_ItemNumber = pos.m_ItemNumber;

            return *this;
        }

        const XFindPos& operator = (const size_t ItemNumber)
        {
            m_ItemNumber = ItemNumber;
            m_bValid = true;

            return *this;
        }


        const size_t ItemNumber() const     { return m_ItemNumber; }



    protected:

        size_t      m_ItemNumber;
        bool        m_bValid;
    };

public:
    CViewSearchEngine(CTracesView& rView);
    virtual ~CViewSearchEngine();

    const CViewItemHighlighterRef   Highlighter() const             { return m_refHighlighter; }
    CViewItemHighlighterRef&         Highlighter()                  { return m_refHighlighter; }

    const XFindPos&     FoundPos() const            { return m_FoundPos; }

    void Next();
    void Previous();
    void Clear();

    CTracesView&    View()      { return m_rView; }

protected:

    CTracesView&                            m_rView;
    XFindPos                                m_FoundPos;
    CViewItemHighlighterRef                 m_refHighlighter;
    CViewItemHighlighter_SearchedLineRef    m_refSearchedLineHighlighter;

};


#endif // _VIEWSEARCHENGINE_HPP_
