#include "HighlightTreeItem.hpp"
#include "HighlightTreeItemEventsConnection.h"
#include "TracesView.h"
#include "View/ViewSearchEngine.h"

/**
 *
 */
CHighlightTreeItem::CHighlightTreeItem(CViewSearchEngine* pSearchEngine) : QTreeWidgetItem(),
    m_pColorBtn(NULL),
    m_pBtnSearchNext(NULL),
    m_pBtnSearchPrevious(NULL),
    m_pSearchEngine(pSearchEngine),
    m_pEventsConnector(NULL)
{
    m_refTextPattern = new CViewItemPattern_Text();

    m_refHighlighter = new CViewItemHighlighter();
    m_refHighlighter->Pattern() = (CViewItemPattern*)m_refTextPattern;

    m_pSearchEngine->View().Highlighters()->Add( (CViewItemHighlighter*)m_refHighlighter );

    m_pColorBtn = new CWordHighlightColorBtn();

    m_pBtnSearchNext = new QToolButton();
    m_pBtnSearchNext->setIcon( QIcon(":/HighlightsMgrWnd/SearchNext") );
    //m_pBtnSearchNext->setIconSize( QSize(32, 32) );

    m_pBtnSearchPrevious = new QToolButton();
    m_pBtnSearchPrevious->setIcon( QIcon(":/HighlightsMgrWnd/SearchPrevious") );
    //m_pBtnSearchPrevious->setIconSize( QSize(32, 32) );

    setFlags( Qt::ItemIsEditable | flags() );

    m_pEventsConnector = new CHighlightTreeItemEventsConnection(this);
    
    m_pEventsConnector->connect(    m_pColorBtn, SIGNAL(OnWordHighlightChanged(CWordHighlightColorBtn*)),
                                    m_pEventsConnector, SLOT(OnWordHighlightChanged(CWordHighlightColorBtn*)));
    m_pEventsConnector->connect(    m_pBtnSearchNext, SIGNAL(clicked()),
                                    m_pEventsConnector, SLOT(OnSearchNext()));
    m_pEventsConnector->connect(    m_pBtnSearchPrevious, SIGNAL(clicked()),
                                    m_pEventsConnector, SLOT(OnSearchPrevious()));
}


/**
 *
 */
CHighlightTreeItem::~CHighlightTreeItem()
{
}

