#ifndef _HIGHLIGHTTREEITEM_HPP_
#define _HIGHLIGHTTREEITEM_HPP_

#include "ViewItemHighlighter.hpp"
#include "ViewItemPattern_Text.hpp"
#include "Color/ColorBtn.h"

#include <QTreeWidgetItem>

class CTracesView;
class CViewSearchEngine;
class CHighlightTreeItemEventsConnection;

/**
 *
 */
class CHighlightTreeItem : public QTreeWidgetItem
{
    friend class CHighlightTreeItemEventsConnection;

public:
    CHighlightTreeItem(CViewSearchEngine* pSearchEngine);
    virtual ~CHighlightTreeItem();

    const CViewItemHighlighterRef       Highlighter() const         { return m_refHighlighter; }

    const CViewItemPattern_TextRef      Pattern() const             { return m_refTextPattern; }
    CViewItemPattern_TextRef            Pattern()                   { return m_refTextPattern; }

    CColorBtn*      ColorBtn() const            { return m_pColorBtn; }
    QToolButton*    SearchNextBtn() const       { return m_pBtnSearchNext; }
    QToolButton*    SearchPreviousBtn() const   { return m_pBtnSearchPrevious; }

protected:

    CViewItemHighlighterRef                 m_refHighlighter;
    CViewItemPattern_TextRef                m_refTextPattern;
    CColorBtn*                              m_pColorBtn;
    QToolButton*                            m_pBtnSearchNext;
    QToolButton*                            m_pBtnSearchPrevious;
    CViewSearchEngine*                      m_pSearchEngine;
    CHighlightTreeItemEventsConnection*     m_pEventsConnector;
};


#endif // _HIGHLIGHTTREEITEM_HPP_

