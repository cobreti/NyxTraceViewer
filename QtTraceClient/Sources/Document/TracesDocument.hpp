#ifndef TRACESREPOSITORYDOC_HPP
#define TRACESREPOSITORYDOC_HPP

#include <QObject>
#include <QTimer>
#include <list>

#include "RepositoryObserver.hpp"
#include "View/ViewItems.hpp"
#include "View/ViewSettings.hpp"
#include "View/IViewItemsModulesListener.hpp"
#include "TracesPool.hpp"
#include "Document/DocRepositoryObserver.hpp"

class CTracesView;
class QWidget;
class CViewItemsModulesMgr;


class CTracesDocument : public QObject,
                        public IViewItemsModulesListener
{
Q_OBJECT

public:

	typedef std::list<CTracesView*>										TracesViewList;

public:
    CTracesDocument(QWidget* pDefaultViewsParentWindow, const QString& name);
    virtual ~CTracesDocument();

    virtual void Init();
    virtual void Destroy();

    virtual CTracesView* CreateView(QWidget* pParent);
	virtual void GetViews( TracesViewList& ViewsList ) const;

    virtual void AddRepositorySrc( TraceClientCore::CTracesPool& rSrcPool );
	virtual void RemoveRepositorySrc( TraceClientCore::CTracesPool& rSrcPool );
	virtual bool Contains( const TraceClientCore::CTracesPool& rSrcPool );

    void OnNewTraceItems(CViewItems* pViewItems);

	const QString& Name() const { return m_Name; }
	QString& Name() { return m_Name; }

    CViewSettings&          DefaultViewSettings()              { return m_DefaultViewSettings; }
    const CViewSettings&    DefaultViewSettings() const        { return m_DefaultViewSettings; }

    Nyx::CMemoryPool*       MemoryPool() const      { return m_refMemoryPool; }

    CViewItemsModulesMgr&           ViewItemsModulesMgr()           { return *m_pViewItemsModulesMgr; }
    const CViewItemsModulesMgr&     ViewItemsModulesMgr() const     { return *m_pViewItemsModulesMgr; }

public: // IViewItemsModulesListener methods

    virtual void OnNewModuleViewItems( CModuleViewItems* pModule );
    virtual void OnNewSessionViewItems( CModuleViewItems* pModule, CSessionViewItems* pSession );

public slots:

    void OnNewTraceItemsHandler(CViewItems* pViewItems);
    void OnRefreshTimer();

Q_SIGNALS:

    void sig_OnNewTraceItems(CViewItems* pViewItems);

protected:

    TracesViewList                              m_Views;
    QWidget*                                    m_pDefaultViewsParentWindow;
    QString                                     m_Name;
    CViewSettings                               m_DefaultViewSettings;

    QTimer                                      m_RefreshTimer;
    CDocRepositoryObserver*                     m_pRepositoryObserver;
    Nyx::CMemoryPoolRef                         m_refMemoryPool;
    size_t                                      m_NextLineId;

    CViewItemsModulesMgr*                       m_pViewItemsModulesMgr;
};

#endif // TRACESREPOSITORYDOC_HPP