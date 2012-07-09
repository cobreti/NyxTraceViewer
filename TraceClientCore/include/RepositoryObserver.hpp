#ifndef REPOSITORYOBSERVER_HPP
#define REPOSITORYOBSERVER_HPP

#include <Nyx.hpp>

namespace TraceClientCore
{
    class CTraceData;

    /**
     *
     */
	class CRepositoryObserver
	{
	public:
		CRepositoryObserver();
		virtual ~CRepositoryObserver();

        virtual void BeginUpdate();
        virtual void EndUpdate();
        virtual void Insert( CTraceData* pTraceData );
        virtual void BeginClear( const Nyx::CAString& ModuleName );
        virtual void EndClear( const Nyx::CAString& ModuleName );

	protected:

        virtual void OnFirstBeginUpdate();
        virtual void OnFinalEndUpdate();

    protected:

        size_t      m_UpdatesCounter;
	};
}

#endif // REPOSITORYOBSERVER_HPP
