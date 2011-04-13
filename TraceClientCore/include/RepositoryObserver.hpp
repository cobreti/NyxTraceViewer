#ifndef REPOSITORYOBSERVER_HPP
#define REPOSITORYOBSERVER_HPP

#include <Nyx.hpp>
#include "TraceDataRepositoryLinkCollection.hpp"
#include "RepositoryObserverNotificationsHandler.hpp"

namespace TraceClientCore
{
    /**
     *
     */
	class IRepositoryObserver
	{
	public:
		virtual void Start() = 0;
		virtual void Stop() = 0;
		virtual TraceClientCore::CTraceDataRepositoryLinkCollection& Links() = 0;
		virtual void ProcessCheck() = 0;
		virtual CRepositoryObserverNotificationsHandlerRef& NotificationsHandler() = 0;
		virtual CRepositoryObserverNotificationsHandlerRef NotificationsHandler() const = 0;
	};


    /**
     *
     */
	class CRepositoryObserver : public Nyx::CMTInterfaceAccess<CRepositoryObserver, IRepositoryObserver>
	{
	public:
		CRepositoryObserver();
		~CRepositoryObserver();

	protected: // IRepositoryObserver methods

		virtual void Start();
		virtual void Stop();
		virtual TraceClientCore::CTraceDataRepositoryLinkCollection& Links()    { return m_RepositoryLinks; }
		virtual void ProcessCheck();
		virtual CRepositoryObserverNotificationsHandlerRef& NotificationsHandler();
		virtual CRepositoryObserverNotificationsHandlerRef NotificationsHandler() const;

		virtual bool MTCancelLock() const { return m_bStopping; }

	protected:

		Nyx::CThreadRef                                         m_refThread;
		TraceClientCore::CTraceDataRepositoryLinkCollection     m_RepositoryLinks;
		CRepositoryObserverNotificationsHandlerRef				m_refNotificationsHandler;
		bool													m_bStopping;
	};
}

#endif // REPOSITORYOBSERVER_HPP
