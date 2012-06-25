#ifndef _HIGHLIGHTTREEITEM_HPP_
#define _HIGHLIGHTTREEITEM_HPP_

#include "ViewItemHighlighter.hpp"
#include "ViewItemPattern_Text.hpp"
#include "Color/ColorBtn.h"

#include <QTreeWidgetItem>

/**
 *
 */
class CHighlightTreeItem : public QTreeWidgetItem
{
public:
    CHighlightTreeItem();
    virtual ~CHighlightTreeItem();

    const CViewItemHighlighterRef       Highlighter() const         { return m_refHighlighter; }

    CColorBtn*      ColorBtn() const            { return m_pColorBtn; }
    QToolButton*    SearchNextBtn() const       { return m_pBtnSearchNext; }
    QToolButton*    SearchPreviousBtn() const   { return m_pBtnSearchPrevious; }

protected:

    CViewItemHighlighterRef         m_refHighlighter;
    CViewItemPattern_TextRef        m_refTextPattern;
    CColorBtn*                      m_pColorBtn;
    QToolButton*                    m_pBtnSearchNext;
    QToolButton*                    m_pBtnSearchPrevious;
};


#endif // _HIGHLIGHTTREEITEM_HPP_

