#ifndef _TRACECLIENTCOREMODULE_HPP_
#define _TRACECLIENTCOREMODULE_HPP_

#include "TracesPoolCollection.hpp"

namespace TraceClientCore
{
    class CPoolsUpdateClock;

	class CModule
	{
	public:
	
		static CModule& Instance();
	
	public:
		CModule();
		virtual ~CModule();

		CTracesPoolCollection&  TracesPools()			{ return m_TracesPools; }
		
        CPoolsUpdateClock&      PoolsUpdateClock()      { return *m_pPoolsUpdateClock; }

	protected:
	
		CTracesPoolCollection				m_TracesPools;
        CPoolsUpdateClock*                  m_pPoolsUpdateClock;
	
		static CModule*						s_pInstance;
	};
}


#endif // _TRACECLIENTCOREMODULE_HPP_
