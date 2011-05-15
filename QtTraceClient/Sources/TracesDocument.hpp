#ifndef TRACESREPOSITORYDOC_HPP
#define TRACESREPOSITORYDOC_HPP

#include <QObject>
#include <QTimer>
#include <list>

#include "RepositoryObserver.hpp"
#include "View/ViewItems.hpp"
#include "View/ViewSettings.hpp"
#include "TracesPool.hpp"
#include "Document/DocRepositoryObserver.hpp"

class CTracesView;
class CTraceDataRepositoryToDocumentLink;
class QWidget;

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

    CViewItems& ViewItems()     { return m_ViewItems; }

public slots:

    void OnNewTraceItemsHandler(CViewItems* pViewItems);
    void OnRefreshTimer();

Q_SIGNALS:

    void sig_OnNewTraceItems(CViewItems* pViewItems);

protected:

    typedef std::list<CTraceDataRepositoryToDocumentLink*>         LinksList;

protected:

    TracesViewList                              m_Views;
    //TraceClientCore::CRepositoryObserver        m_RepositoryObserver;
    QWidget*                                    m_pDefaultViewsParentWindow;
    LinksList                                   m_UsedLinks;
    QString                                     m_Name;
    CViewSettings                               m_DefaultViewSettings;

    CViewItems                                  m_ViewItems;
    QTimer                                      m_RefreshTimer;
    CDocRepositoryObserver                      m_RepositoryObserver;
};

#endif // TRACESREPOSITORYDOC_HPP
