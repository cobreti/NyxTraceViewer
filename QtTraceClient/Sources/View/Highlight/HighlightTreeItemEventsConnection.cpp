#include "HighlightTreeItemEventsConnection.h"
#include "HighlightTreeItem.hpp"
#include "Color/ColorBtn.h"
#include "TracesView.h"


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
    m_pOwner->m_pView->update();
}
