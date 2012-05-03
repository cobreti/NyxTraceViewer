#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "TraceClientCoreModule.hpp"
#include "TracesView.h"
#include "View/ViewItemsNodeObjectsPool.hpp"
#include "View/Walkers/ViewItemsWalkerNodesPool.hpp"

#include <QMainWindow>

class CPipesMgntPage;
class CViewPage;
class QTreeWidgetItem;

namespace Ui {
    class MainWindow;
}

class CTracesDocument;

class CMainWindow : public QMainWindow {
    Q_OBJECT
public:
    CMainWindow(QWidget *parent = 0);
    ~CMainWindow();

    void PinView( CTracesView* pView );
    void UnpinView( CTracesView* pView );

public slots:

	//void OnDump();
    void OnViewsTreeSelectionChanged();
    void OnAddView();
    void OnCopyView();
    void OnViewItemChanged( QTreeWidgetItem* pItem, int );
    void OnToggleTreePanel();

protected:

	void changeEvent(QEvent *e);
	void closeEvent(QCloseEvent *e);

    void CloseChildViews( QTreeWidgetItem* pParent );
//    virtual CTracesDocument* CreateNewDocument(  const QString& rDocumentName );
    virtual CTracesView* CreateNewView( const QString& ViewName, QTreeWidgetItem* pParent = NULL );
    virtual void SelectItemWithView( CTracesView* pView );
    void ShowLeftPanel(bool bShow);

    void InitToolbar();

private:
    Ui::MainWindow *ui;

//    CDocumentsCollection        m_Documents;
    int                         m_nNextDocumentId;
    int                         m_nNextViewId;
    CViewPage*                  m_pViewPage;
    CViewItemsNodeObjectsPool   m_ViewNodeObjectsPool;
    CViewItemsWalkerNodesPool   m_ViewItemsWalkerNodesPool;
    int                         m_LeftSplitterAreaWidth;
};

#endif // MAINWINDOW_H
