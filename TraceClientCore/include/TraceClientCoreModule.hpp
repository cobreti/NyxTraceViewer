#ifndef _TRACECLIENTCOREMODULE_HPP_
#define _TRACECLIENTCOREMODULE_HPP_

#include "TracesPoolCollection.hpp"

namespace TraceClientCore
{
	class CModule
	{
	public:
	
		static CModule& Instance();
	
	public:
		CModule();
		virtual ~CModule();
		
		CTracesPoolCollection& TracesPools()			{ return m_TracesPools; }
		
	protected:
	
		CTracesPoolCollection				m_TracesPools;
	
		static CModule*						s_pInstance;
	};
}


#endif // _TRACECLIENTCOREMODULE_HPP_
