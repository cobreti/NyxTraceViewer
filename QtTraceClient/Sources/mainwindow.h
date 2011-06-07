#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Document/DocumentsCollection.hpp"
#include "TraceClientCoreModule.hpp"
#include "TracesView.h"
#include "View/ViewItemsNodeObjectsPool.hpp"

#include <QMainWindow>

class CPipesMgntPage;
class CViewPage;

namespace Ui {
    class MainWindow;
}

class CDebugPanel;
class CTracesDocument;

class CMainWindow : public QMainWindow {
    Q_OBJECT
public:
    CMainWindow(QWidget *parent = 0);
    ~CMainWindow();

public slots:

	//void OnDump();
    void OnViewsTreeSelectionChanged();
    void OnAddView();

protected:

	void changeEvent(QEvent *e);
	void closeEvent(QCloseEvent *e);

    virtual CTracesDocument* CreateNewDocument(  const QString& rDocumentName );
    virtual CTracesView* CreateNewView( CTracesDocument* pDoc, const QString& ViewName );

private:
    Ui::MainWindow *ui;

    CDebugPanel*                m_pDebugPanel;
	CDocumentsCollection	    m_Documents;
    int                         m_nNextDocumentId;
    int                         m_nNextViewId;
    CViewPage*                  m_pViewPage;
    CViewItemsNodeObjectsPool   m_ViewNodeObjectsPool;
};

#endif // MAINWINDOW_H
