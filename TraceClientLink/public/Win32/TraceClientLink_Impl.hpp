#ifndef _TRACECLIENTLINK_IMPL_HPP_
#define _TRACECLIENTLINK_IMPL_HPP_

#include <Windows.h>
#include "TraceClientLink.hpp"

class CTraceClientLink_Impl : public CTraceClientLink
{
	typedef unsigned int (__cdecl *PFCTCreateTraceLink)( const char* szName, int nType );
	typedef void (__cdecl *PFCTReleaseTraceLink)( const unsigned int& id );
	typedef void (__cdecl *PFCTWriteTraceA)( const unsigned int& id, const char* szData, va_list args );
	typedef void (__cdecl *PFCTWriteTraceW)( const unsigned int& id, const wchar_t* wszData, va_list args );

public:

	static void CreateInstance(const char* szTraceLinkName, ECharType charType);
	static void ReleaseInstance();
	static void CreateInstance(HINSTANCE hDll, const char* szTraceLinkName);
	static CTraceClientLink& Instance();

public:
	CTraceClientLink_Impl(const char* szTraceLinkName, ECharType charType);
	virtual ~CTraceClientLink_Impl();

	virtual void Write( const char* szData, ... );
    virtual void Write( const wchar_t* wszData, ... );

protected:

	HINSTANCE							m_hDLLInstance;
	PFCTCreateTraceLink				    m_pfctCreateTraceLink;
	PFCTReleaseTraceLink				m_pfctReleaseTraceLink;
	PFCTWriteTraceA						m_pfctWriteTraceA;
	PFCTWriteTraceW						m_pfctWriteTraceW;
	unsigned int						m_id;

	static CTraceClientLink_Impl*		s_pInstance;
};


#endif // _TRACECLIENTLINK_IMPL_HPP_

