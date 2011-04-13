#ifndef _TRACESVIEWCONTROLLER_HPP_
#define _TRACESVIEWCONTROLLER_HPP_

#include "TracesPoolsCollection.hpp"


using namespace System::Windows::Forms;

ref class CTracesView;
class CUITraceDataRepository;
class CUIRepositoryUpdater;


public ref class CTracesViewController
{
public:

	delegate void OnReposUpdate_Delegate(void*);

public: // protected functions
	CTracesViewController(CTracesView^ View);
	virtual ~CTracesViewController();

	virtual property CUITraceDataRepository& Repository
	{
		CUITraceDataRepository& get() { return *m_pRepository; }
	}

	virtual void OnTest_UpdateUIRepos();

	property OnReposUpdate_Delegate^ ReposUpdate
	{
		OnReposUpdate_Delegate^ get() { return m_ReposUpdateDelegate; }
		void set( OnReposUpdate_Delegate^ pDelegate ) { m_ReposUpdateDelegate = pDelegate; }
	}

protected: // protected methods

	void CreateRepository();
	void OnReposUpdate(void* pParam);

	void AddSrcPool( const wchar_t* wszName );

	void OnViewClosed( System::Object^ sender, System::EventArgs^ args );

protected: // protected members

	CTracesView^							m_TracesView;
	CUITraceDataRepository*					m_pRepository;
	CUIRepositoryUpdater*					m_pRepositoryUpdater;
	OnReposUpdate_Delegate^					m_ReposUpdateDelegate;
	CTracesPoolsCollection*					m_pTracesPools;
};


#endif // _TRACESVIEWCONTROLLER_HPP_

