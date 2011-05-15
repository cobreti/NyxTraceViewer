#ifndef _DBGTRACESFEEDER_HPP_
#define _DBGTRACESFEEDER_HPP_

#include <Nyx.hpp>

#include "TraceFeeder.hpp"
#include "DbgTracesFeederCore.hpp"

namespace TraceClientCore
{
	class CDbgTracesFeeder : public CTraceFeeder
	{
	public:
		CDbgTracesFeeder( CTracesPool* pOwnerPool );
		virtual ~CDbgTracesFeeder();

		virtual void Start();
		virtual void Stop();
		virtual bool IsRunning() const;
		virtual void StartFeed( const int& nCount,
								const int& nDelayBetweenTraces );

	protected:

//		CDbgTracesFeederCore			m_Core;
	};
}

#endif // _DBGTRACESFEEDER_HPP_
