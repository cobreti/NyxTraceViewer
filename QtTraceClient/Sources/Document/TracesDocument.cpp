#include "TracesDocument.hpp"
#include "TracesView.h"
#include "TraceClientApp.hpp"

#include "TracesPool.hpp"
#include "View/ViewColumnSettings.hpp"
#include "View/ViewItem.hpp"
#include "View/ViewItemsModulesMgr.hpp"

/**
 *
 */
CTracesDocument::CTracesDocument(QWidget* pDefaultViewsParentWindow, const QString& name) :
m_pDefaultViewsParentWindow(pDefaultViewsParentWindow),
m_Name(name)
{
    m_refViewCore = new CTracesViewCore();
}


/**
 *
 */
CTracesDocument::~CTracesDocument()
{
}


/**
 *
 */
void CTracesDocument::Init()
{
}


/**
 *
 */
void CTracesDocument::Destroy()
{
    CTracesViewSetIterator      iter = m_refViewCore->GetViewsIterator();

    while ( iter.Valid() )
    {
        iter.View()->close();
        iter.MoveToNext();
    }
}


/**
 *
 */
//CTracesView* CTracesDocument::CreateView(QWidget* pParent)
//{
//    CTracesView*        pView = new CTracesView(*this, pParent);

//    m_refViewCore->AddView(pView);

//    pView->Settings().ViewItemsSettings() = CTraceClientApp::Instance().AppSettings().DefaultViewSettings().ViewItemsSettings();//DefaultViewSettings().ViewItemsSettings();
//    pView->setParent(NULL, Qt::Window);

//    return pView;
//}


/**
 *
 */
void CTracesDocument::GetViews( CTracesDocument::TracesViewList& ViewsList ) const
{
    CTracesViewSetIterator      iter = m_refViewCore->GetViewsIterator();

    while (iter.Valid())
    {
        ViewsList.push_back(iter.View());
        iter.MoveToNext();
    }
}


/**
 *
 */
CViewItemsModulesMgr& CTracesDocument::ViewItemsModulesMgr()
{
    return m_refViewCore->ViewItemsModulesMgr();
}


/**
 *
 */
const CViewItemsModulesMgr& CTracesDocument::ViewItemsModulesMgr() const
{
    return m_refViewCore->ViewItemsModulesMgr();
}
