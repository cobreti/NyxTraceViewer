#ifndef _TRACECLIENTLINK_IMPL_HPP_
#define _TRACECLIENTLINK_IMPL_HPP_

#include <dlfcn.h>
#include <stdarg.h>
#include "TraceClientLink.hpp"


class CTraceClientLink_Impl : public CTraceClientLink
{
	typedef unsigned int (*PFCTCreateTraceLink)( const char* szName, int nType );
	typedef void (*PFCTReleaseTraceLink)( const unsigned int& id );
	typedef void (*PFCTWriteTraceA)( const unsigned int& id, const char* szData, va_list args );
	typedef void (*PFCTWriteTraceW)( const unsigned int& id, const wchar_t* wszData, va_list args );

public:

	static void CreateInstance(const char* szTraceLinkName, ECharType charType);
	static void ReleaseInstance();
	static void CreateInstance(void* pModule, const char* szTraceLinkName);
    static CTraceClientLink& Instance();

public:
	CTraceClientLink_Impl(const char* szTraceLinkName, ECharType charType);
	virtual ~CTraceClientLink_Impl();

	virtual void Write( const char* szData, ... );
    virtual void Write( const wchar_t* wszData, ... );

protected:

    void*								m_pModule;
	PFCTCreateTraceLink				    m_pfctCreateTraceLink;
	PFCTReleaseTraceLink				m_pfctReleaseTraceLink;
	PFCTWriteTraceA						m_pfctWriteTraceA;
	PFCTWriteTraceW						m_pfctWriteTraceW;
	unsigned int						m_id;

	static CTraceClientLink_Impl*		s_pInstance;
};


#endif // _TRACECLIENTLINK_LINUX_HPP_

