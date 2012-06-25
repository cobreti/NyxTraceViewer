#include "HighlightsMgrWnd.h"
#include "HighlightTreeItemDelegate.hpp"
#include "HighlightTreeItem.hpp"
#include "TracesView.h"
#include "View/ViewSearchEngine.h"

#include "ui_HighlightsMgrWnd.h"

/**
 *
 */
CHighlightsMgrWnd::CHighlightsMgrWnd(CViewSearchEngine* pSearchEngine, QWidget* parent) : QWidget(parent),
ui(new Ui::HighlightsMgrWnd),
m_pSearchEngine(pSearchEngine),
m_pTreeItemDelegate(NULL)
{
    ui->setupUi(this);

    hide();
    setWindowFlags( Qt::Tool );

    m_pTreeItemDelegate = new CHighlightTreeItemDelegate(ui->treeWidget);
    ui->treeWidget->setItemDelegateForColumn(0, m_pTreeItemDelegate);
    ui->treeWidget->setItemDelegateForColumn(1, m_pTreeItemDelegate);
    ui->treeWidget->setItemDelegateForColumn(2, m_pTreeItemDelegate);
    ui->treeWidget->setItemDelegateForColumn(3, m_pTreeItemDelegate);

    for (size_t index = 0; index < 10; ++index)
        ui->treeWidget->addTopLevelItem(new CHighlightTreeItem(m_pSearchEngine));

    bool bRet = connect( ui->treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(OnItemChanged(QTreeWidgetItem*, int)));
}


/**
 *
 */
CHighlightsMgrWnd::~CHighlightsMgrWnd()
{
    delete m_pTreeItemDelegate;
}


/**
 *
 */
void CHighlightsMgrWnd::Show(const QPoint& pt, const QSize& size)
{
    //setWindowFlags(Qt::Popup);

    QSize   orgSize = this->size();

    move(pt);
    resize(orgSize.width(), size.height());
    show();
}


/**
 *
 */
void CHighlightsMgrWnd::showEvent(QShowEvent* pShowEvent)
{
    QRect       rcRow = ui->treeWidget->rect();

    ui->treeWidget->setColumnWidth(0, 32);
    ui->treeWidget->setColumnWidth(1, rcRow.width() - 32*3 - ui->treeWidget->indentation() );
    ui->treeWidget->setColumnWidth(2, 32);
    ui->treeWidget->setColumnWidth(3, 32);    
}


/**
 *
 */
void CHighlightsMgrWnd::resizeEvent(QResizeEvent*)
{
    QRect       rcRow = ui->treeWidget->rect();

    ui->treeWidget->setColumnWidth(0, 32);
    ui->treeWidget->setColumnWidth(1, rcRow.width() - 32*3 );
    ui->treeWidget->setColumnWidth(2, 32);
    ui->treeWidget->setColumnWidth(3, 32);    
}


/**
 *
 */
void CHighlightsMgrWnd::OnItemChanged(QTreeWidgetItem* pItem, int column)
{
    if ( column == 1 )
    {
        CHighlightTreeItem*     pHighlightItem = static_cast<CHighlightTreeItem*>(pItem);

        pHighlightItem->Pattern()->TextToMatch() = pItem->text(1);
        m_pSearchEngine->View().update();
    }
}

