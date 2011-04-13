#ifndef _UIREPOSITORYUPDATER_HPP_
#define _UIREPOSITORYUPDATER_HPP_

#include <Nyx.hpp>

#include "TraceDataReposLinksCollection.hpp"


/**
 *
 */
class IUIRepositoryUpdater
{
public:

	virtual CTraceDataReposLinksCollection& Links() = 0;
	virtual void Update() = 0;
	virtual void Start() = 0;
	virtual void Stop() = 0;
};


/**
 *
 */
class CUIRepositoryUpdater : public Nyx::CMTInterfaceAccess<CUIRepositoryUpdater, IUIRepositoryUpdater>
{
public: // public methods
	CUIRepositoryUpdater( Nyx::CDelegateBase<>* pCallback );
	virtual ~CUIRepositoryUpdater();

protected: // protected methods

	virtual CTraceDataReposLinksCollection& Links();
	virtual void Update();
	virtual void Start();
	virtual void Stop();

protected: // protected members

	CTraceDataReposLinksCollection		m_Links;
	Nyx::CRef<Nyx::CDelegateBase<>>		m_refUICallback;
	Nyx::CThreadRef						m_refThread;
};


#endif // _UIREPOSITORYUPDATER_HPP_
