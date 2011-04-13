#ifndef _REPOSITORYOBSERVERNOTIFICATIONSHANDLER_HPP_
#define _REPOSITORYOBSERVERNOTIFICATIONSHANDLER_HPP_

#include <Nyx.hpp>

namespace TraceClientCore
{
    class CTraceInserter;
    
	DECLARE_OBJECTREF(CRepositoryObserverNotificationsHandler);

	class CRepositoryObserverNotificationsHandler : public Nyx::CRefCount_Impl<>
	{
	public:
		CRepositoryObserverNotificationsHandler();
		
		virtual void OnNewItems() {}
        virtual CTraceInserter* OnBeginCheckUpdate() { return NULL; }
        virtual void OnEndCheckUpdate() {}
		
	protected:
		
		virtual ~CRepositoryObserverNotificationsHandler();
	};
}

#endif // _REPOSITORYOBSERVERNOTIFICATIONSHANDLER_HPP_
