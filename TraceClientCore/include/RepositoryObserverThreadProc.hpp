#ifndef REPOSITORYOBSERVERTHREADPROC_HPP
#define REPOSITORYOBSERVERTHREADPROC_HPP

#include <Nyx.hpp>


namespace TraceClientCore
{
	class CRepositoryObserver;

	/**
	 *
	 */
	class CRepositoryObserverThreadProc : public Nyx::CObject_Impl<Nyx::CThreadProc>
	{
	public:
		CRepositoryObserverThreadProc(CRepositoryObserver& rRepositoryObserver);
		~CRepositoryObserverThreadProc();

		virtual void Run();
		virtual void Stop();

	protected:

		CRepositoryObserver&                    m_rRepositoryObserver;
		bool                                    m_bRunning;
		Nyx::CEventRef                          m_refEvent;
		Nyx::UInt32                             m_Timeout;
	};
}

#endif // REPOSITORYOBSERVERTHREADPROC_HPP
