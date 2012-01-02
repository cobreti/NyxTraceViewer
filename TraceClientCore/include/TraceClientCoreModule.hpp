#ifndef _TRACECLIENTCOREMODULE_HPP_
#define _TRACECLIENTCOREMODULE_HPP_

#include "TracesPoolCollection.hpp"
#include "TcpModule.hpp"

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
        
        CTcpModule&             TcpModule()             { return m_TcpModule; }

	protected:
	
		CTracesPoolCollection				m_TracesPools;
        CPoolsUpdateClock*                  m_pPoolsUpdateClock;
        CTcpModule                          m_TcpModule;
	
		static CModule*						s_pInstance;
	};
}


#endif // _TRACECLIENTCOREMODULE_HPP_
