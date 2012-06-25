#include "HighlightTreeItem.hpp"
#include "HighlightTreeItemEventsConnection.h"
#include "TracesView.h"

/**
 *
 */
CHighlightTreeItem::CHighlightTreeItem(CTracesView* pView) : QTreeWidgetItem(),
    m_pColorBtn(NULL),
    m_pBtnSearchNext(NULL),
    m_pBtnSearchPrevious(NULL),
    m_pView(pView),
    m_pEventsConnector(NULL)
{
    m_refTextPattern = new CViewItemPattern_Text();

    m_refHighlighter = new CViewItemHighlighter();
    m_refHighlighter->Pattern() = (CViewItemPattern*)m_refTextPattern;

    m_pView->Highlighters()->Add( (CViewItemHighlighter*)m_refHighlighter );

    m_pColorBtn = new CWordHighlightColorBtn();

    m_pBtnSearchNext = new QToolButton();
    m_pBtnSearchNext->setIcon( QIcon(":/HighlightsMgrWnd/SearchNext") );
    //m_pBtnSearchNext->setIconSize( QSize(32, 32) );

    m_pBtnSearchPrevious = new QToolButton();
    m_pBtnSearchPrevious->setIcon( QIcon(":/HighlightsMgrWnd/SearchPrevious") );
    //m_pBtnSearchPrevious->setIconSize( QSize(32, 32) );

    setFlags( Qt::ItemIsEditable | flags() );

    m_pEventsConnector = new CHighlightTreeItemEventsConnection(this);
    
    m_pEventsConnector->connect(    m_pColorBtn, SIGNAL(OnColorChanged(CColorBtn*)),
                                    m_pEventsConnector, SLOT(OnColorChanged(CColorBtn*)));
}


/**
 *
 */
CHighlightTreeItem::~CHighlightTreeItem()
{
}

