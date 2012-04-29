#ifndef TRACESREPOSITORYDOC_HPP
#define TRACESREPOSITORYDOC_HPP

#include <QObject>
#include <list>

#include "View/ViewSettings.hpp"
#include "View/IViewItemsModulesListener.hpp"
#include "TracesPool.hpp"
#include "View/TracesViewCore.hpp"

class CTracesView;
class QWidget;
class CViewItemsModulesMgr;
class CTracesViewCore;


class CTracesDocument : public QObject
{
Q_OBJECT

public:

	typedef std::list<CTracesView*>										TracesViewList;

public:
    CTracesDocument(QWidget* pDefaultViewsParentWindow, const QString& name);
    virtual ~CTracesDocument();

    virtual void Init();
    virtual void Destroy();

//    virtual CTracesView* CreateView(QWidget* pParent);
	virtual void GetViews( TracesViewList& ViewsList ) const;

    void OnNewTraceItems(CViewItems* pViewItems);

//	const QString& Name() const { return m_Name; }
//	QString& Name() { return m_Name; }

    CViewItemsModulesMgr&           ViewItemsModulesMgr();
    const CViewItemsModulesMgr&     ViewItemsModulesMgr() const;

    CTracesViewCore*                ViewCore() const        { return m_refViewCore; }

protected:

    QWidget*                                    m_pDefaultViewsParentWindow;
    QString                                     m_Name;
    CViewSettings                               m_DefaultViewSettings;

    CTracesViewCoreRef                          m_refViewCore;
};

#endif // TRACESREPOSITORYDOC_HPP
