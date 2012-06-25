#include "HighlightTreeItem.hpp"


/**
 *
 */
CHighlightTreeItem::CHighlightTreeItem() : QTreeWidgetItem(),
    m_pColorBtn(NULL),
    m_pBtnSearchNext(NULL),
    m_pBtnSearchPrevious(NULL)
{
    m_refTextPattern = new CViewItemPattern_Text();

    m_refHighlighter = new CViewItemHighlighter();
    m_refHighlighter->Pattern() = (CViewItemPattern*)m_refTextPattern;

    m_pColorBtn = new CColorBtn();

    m_pBtnSearchNext = new QToolButton();
    m_pBtnSearchNext->setIcon( QIcon(":/HighlightsMgrWnd/SearchNext") );
    //m_pBtnSearchNext->setIconSize( QSize(32, 32) );

    m_pBtnSearchPrevious = new QToolButton();
    m_pBtnSearchPrevious->setIcon( QIcon(":/HighlightsMgrWnd/SearchPrevious") );
    //m_pBtnSearchPrevious->setIconSize( QSize(32, 32) );

    setFlags( Qt::ItemIsEditable | flags() );
}


/**
 *
 */
CHighlightTreeItem::~CHighlightTreeItem()
{
}

