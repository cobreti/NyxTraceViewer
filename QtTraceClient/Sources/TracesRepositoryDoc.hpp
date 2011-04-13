#ifndef TRACESREPOSITORYDOC_HPP
#define TRACESREPOSITORYDOC_HPP

#include <QObject>
#include <list>

#include "DocTraceDataRepository.hpp"
#include "RepositoryObserver.hpp"
#include "View/ViewItemsSettings.hpp"

class CTracesView;
class CTraceDataRepositoryToDocRepositoryLink;
class QWidget;

class CTracesRepositoryDoc : public QObject
{
Q_OBJECT

public:

	typedef std::list<CTracesView*>										TracesViewList;

public:
    CTracesRepositoryDoc(QWidget* pDefaultViewsParentWindow, const QString& name);
    virtual ~CTracesRepositoryDoc();

    virtual void Init();
    virtual void Destroy();

    virtual CTracesView* CreateView(QWidget* pParent);
	virtual void GetViews( TracesViewList& ViewsList ) const;

    virtual void AddRepositorySrc( TraceClientCore::CTracesPool& rSrcPool );
	virtual void RemoveRepositorySrc( TraceClientCore::CTracesPool& rSrcPool );
	virtual bool Contains( const TraceClientCore::CTracesPool& rSrcPool );

    CDocTraceDataRepository& Repository() { return *m_pRepository; }

    void OnNewTraceItems();

	const QString& Name() const { return m_Name; }
	QString& Name() { return m_Name; }

    CViewItemsSettings& ViewItemsSettings() { return m_ViewItemsSettings; }

public slots:


Q_SIGNALS:

    void sig_OnNewTraceItems();

protected:

    typedef std::list<CTraceDataRepositoryToDocRepositoryLink*>         LinksList;

protected:

    TracesViewList                              m_Views;
    CDocTraceDataRepository*                    m_pRepository;
    TraceClientCore::CRepositoryObserver        m_RepositoryObserver;
    QWidget*                                    m_pDefaultViewsParentWindow;
    LinksList                                   m_UsedLinks;
    QString                                     m_Name;
    CViewItemsSettings                          m_ViewItemsSettings;
};

#endif // TRACESREPOSITORYDOC_HPP
