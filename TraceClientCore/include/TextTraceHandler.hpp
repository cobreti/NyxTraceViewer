#ifndef _CTEXTTRACEHANDLER_HPP_
#define _CTEXTTRACEHANDLER_HPP_

#include <Nyx.hpp>

namespace TraceClientCore
{
	/**
	 *
	 */
	class CTextTraceHandler
	{
	public:
		CTextTraceHandler();
		virtual ~CTextTraceHandler();

		virtual void ParseRawTraceLine(char* szLine, const Nyx::NyxSize& size);
		virtual void HandleTraceLine(char* szModule, char* pThread, char* szContent);
	};
}


#endif // _CTEXTTRACEHANDLER_HPP_
