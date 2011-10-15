#ifndef _TRACECLIENTLINK_WIN32_HPP_
#define _TRACECLIENTLINK_WIN32_HPP_

#include <Windows.h>
#include "TraceClientLink.hpp"

class CTraceClientLink_Win32 : public CTraceClientLink
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
	CTraceClientLink_Win32(const char* szTraceLinkName, ECharType charType);
	virtual ~CTraceClientLink_Win32();

	virtual void Write( const char* szData, ... );
    virtual void Write( const wchar_t* wszData, ... );

protected:

	HINSTANCE							m_hDLLInstance;
	PFCTCreateTraceLink				    m_pfctCreateTraceLink;
	PFCTReleaseTraceLink				m_pfctReleaseTraceLink;
	PFCTWriteTraceA						m_pfctWriteTraceA;
	PFCTWriteTraceW						m_pfctWriteTraceW;
	unsigned int						m_id;

	static CTraceClientLink_Win32*		s_pInstance;
};


#endif // _TRACECLIENTLINK_WIN32_HPP_

