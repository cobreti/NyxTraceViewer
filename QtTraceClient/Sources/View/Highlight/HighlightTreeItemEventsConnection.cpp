#include "HighlightTreeItemEventsConnection.h"
#include "HighlightTreeItem.hpp"
#include "Color/ColorBtn.h"
#include "TracesView.h"
#include "View/ViewSearchEngine.h"


/**
 *
 */
CHighlightTreeItemEventsConnection::CHighlightTreeItemEventsConnection(CHighlightTreeItem* pOwner) : QObject(),
m_pOwner(pOwner)
{
}


/**
 *
 */
CHighlightTreeItemEventsConnection::~CHighlightTreeItemEventsConnection()
{
}


/**
 *
 */
void CHighlightTreeItemEventsConnection::OnColorChanged(CColorBtn* pBtn)
{
    m_pOwner->m_refHighlighter->HighlightColor() = pBtn->Color();
    m_pOwner->m_pSearchEngine->View().update();
}


/**
 *
 */
void CHighlightTreeItemEventsConnection::OnSearchNext()
{
    CViewSearchEngine*  pSearchEngine = m_pOwner->m_pSearchEngine;

    pSearchEngine->Highlighter() = m_pOwner->m_refHighlighter;
    pSearchEngine->Next();
}


/**
 *
 */
void CHighlightTreeItemEventsConnection::OnSearchPrevious()
{
    CViewSearchEngine*  pSearchEngine = m_pOwner->m_pSearchEngine;

    pSearchEngine->Highlighter() = m_pOwner->m_refHighlighter;
    pSearchEngine->Previous();
}

