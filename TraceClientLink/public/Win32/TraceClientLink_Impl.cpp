#include "TraceClientLink_Impl.hpp"
#include <stdio.h>


extern "C" __declspec(dllexport) void __cdecl TraceClientLinkDll_Init(const char* szTraceLinkName, int charType);
extern "C" __declspec(dllexport) void __cdecl TraceClientLinkDll_Release();

/**
 *
 */
void __cdecl TraceClientLinkDll_Init(const char* szTraceLinkName, int charType)
{
    CTraceClientLink::CreateInstance(szTraceLinkName, (CTraceClientLink::ECharType)charType);
}

void __cdecl TraceClientLinkDll_Release()
{
   CTraceClientLink::ReleaseInstance();
}


class CDummyTraceClientLink : public CTraceClientLink
{
public:
   CDummyTraceClientLink() {};
   virtual ~CDummyTraceClientLink() {};

   virtual void Write( const char* szData, ... ) {}
   virtual void Write( const wchar_t* wszData, ... ) {}

};



/**
 *
 */
CTraceClientLink_Impl*			CTraceClientLink_Impl::s_pInstance = NULL;

static CDummyTraceClientLink  s_DummyTraceClientLink;


/**
 *
 */
void CTraceClientLink::CreateInstance(const char* szTraceLinkName, CTraceClientLink::ECharType charType)
{
	CTraceClientLink_Impl::CreateInstance(szTraceLinkName, charType);
}

/**
 *
 */
void CTraceClientLink::CreateDllInstance(HINSTANCE hDll, const char* szTraceLinkName, CTraceClientLink::ECharType charType)
{
   typedef void (__cdecl *TraceClientLinkDll_InitProc)(const char* szTraceLinkName, int);

   TraceClientLinkDll_InitProc         InitProc = (TraceClientLinkDll_InitProc)GetProcAddress(hDll, "_TraceClientLinkDll_Init");

   if ( NULL == InitProc )
        InitProc = (TraceClientLinkDll_InitProc)GetProcAddress(hDll, "TraceClientLinkDll_Init");

   if ( InitProc != NULL )
      InitProc(szTraceLinkName, charType);
   //   MessageBox(NULL, "failure to get TraceClientLink Init Proc", "CTraceClientLink::CreateInstance", MB_OK);
   //else
   //   MessageBox(NULL, "success to get TraceClientLink Init Proc", "CTraceClientLink::CreateInstance", MB_OK);
}


/**
 *
 */
void CTraceClientLink::ReleaseDllInstance(HINSTANCE hDll)
{
   typedef void (__cdecl *TraceClientLinkDll_ReleaseProc)();

   TraceClientLinkDll_ReleaseProc         ReleaseProc = (TraceClientLinkDll_ReleaseProc)GetProcAddress(hDll, "_TraceClientLinkDll_Release");

   if ( ReleaseProc != NULL )
      ReleaseProc();
   //   MessageBox(NULL, "failure to get TraceClientLink Init Proc", "CTraceClientLink::CreateInstance", MB_OK);
   //else
   //   MessageBox(NULL, "success to get TraceClientLink Init Proc", "CTraceClientLink::CreateInstance", MB_OK);
}


/**
 *
 */
void CTraceClientLink::ReleaseInstance()
{
	CTraceClientLink_Impl::ReleaseInstance();
}


/**
 *
 */
CTraceClientLink& CTraceClientLink::Instance()
{
	return CTraceClientLink_Impl::Instance();
}


/**
 *
 */
void CTraceClientLink_Impl::CreateInstance(const char* szTraceLinkName, CTraceClientLink::ECharType charType)
{
   if ( s_pInstance == NULL )
	   s_pInstance = new CTraceClientLink_Impl(szTraceLinkName, charType);
}


/**
 *
 */
void CTraceClientLink_Impl::ReleaseInstance()
{
   if ( s_pInstance != NULL )
   {
	   delete s_pInstance;
      s_pInstance = NULL;
   }
}


/**
 *
 */
CTraceClientLink& CTraceClientLink_Impl::Instance()
{
   if ( s_pInstance != NULL )
	   return *s_pInstance;

   return s_DummyTraceClientLink;
}


/**
 *
 */
CTraceClientLink_Impl::CTraceClientLink_Impl(const char* szTraceLinkName, ECharType charType) :
m_hDLLInstance(NULL),
m_pfctCreateTraceLink(NULL),
m_pfctReleaseTraceLink(NULL),
m_pfctWriteTraceA(NULL),
m_pfctWriteTraceW(NULL),
m_id(0)
{
	m_hDLLInstance = ::LoadLibraryA("TraceClientLink.dll");
	if ( m_hDLLInstance )
	{
		m_pfctCreateTraceLink = (PFCTCreateTraceLink)::GetProcAddress(m_hDLLInstance, "CreateTraceLink");
		m_pfctReleaseTraceLink = (PFCTReleaseTraceLink)::GetProcAddress(m_hDLLInstance, "ReleaseTraceLink");
		m_pfctWriteTraceA = (PFCTWriteTraceA)::GetProcAddress(m_hDLLInstance, "WriteTraceA");
		m_pfctWriteTraceW = (PFCTWriteTraceW)::GetProcAddress(m_hDLLInstance, "WriteTraceW");
	}


	if ( m_pfctCreateTraceLink && m_pfctReleaseTraceLink )
		m_id = m_pfctCreateTraceLink(szTraceLinkName, charType);
}


/**
 *
 */
CTraceClientLink_Impl::~CTraceClientLink_Impl()
{
	if ( m_id > 0 && m_pfctReleaseTraceLink )
		m_pfctReleaseTraceLink(m_id);

	if ( m_hDLLInstance )
		::FreeLibrary(m_hDLLInstance);
}


/**
 *
 */
void CTraceClientLink_Impl::Write(const char* szData, ...)
{
	if ( m_id > 0 && m_pfctWriteTraceA )
    {
        va_list args;
        va_start(args, szData);
		m_pfctWriteTraceA(m_id, szData, args);
        va_end(args);
    }
}


/**
 *
 */
void CTraceClientLink_Impl::Write( const wchar_t* wszData, ... )
{
	if ( m_id > 0 && m_pfctWriteTraceW )
    {
        va_list args;
        va_start(args, wszData);
		m_pfctWriteTraceW(m_id, wszData, args);
        va_end(args);
    }
}