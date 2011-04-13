#ifndef _UIREPOSITORYUPDATERTHREADPROC_HPP_
#define _UIREPOSITORYUPDATERTHREADPROC_HPP_

#include <Nyx.hpp>
#include <NyxObject_Impl.hpp>

class CUIRepositoryUpdater;

class CUIRepositoryUpdaterThreadProc : public Nyx::CObject_Impl<Nyx::CThreadProc>
{
public:
	CUIRepositoryUpdaterThreadProc( CUIRepositoryUpdater& rUpdater );
	virtual ~CUIRepositoryUpdaterThreadProc();

	virtual void Run();
	virtual void Stop();

protected:

	CUIRepositoryUpdater&		m_rUpdater;
	bool						m_bRunning;
	Nyx::CEventRef				m_refEvent;

};


#endif // _UIREPOSITORYUPDATERTHREADPROC_HPP_
