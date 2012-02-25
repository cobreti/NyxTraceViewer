#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <Nyx.hpp>
#include <NyxNet.hpp>

class CTracePipeReceiver;


/**
 *
 */
class CApplication
{
public:

	static CApplication& Instance();

public:
	CApplication();
	virtual ~CApplication();

	virtual void Init();
	virtual void Run();
	virtual void Terminate();

	virtual void SignalTerminate();

protected:

	virtual void SetCancelHandlers();

protected:

	static CApplication*		s_pInstance;

	Nyx::CEventRef      		m_refTerminateEvent;
	CTracePipeReceiver*			m_pReceiver;
};


#endif // _APPLICATION_HPP_
