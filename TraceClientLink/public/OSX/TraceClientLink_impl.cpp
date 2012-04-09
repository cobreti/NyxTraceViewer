#include "TraceClientLink_Impl.hpp"

#include <stdio.h>
#include <stdarg.h>


/**
 *
 */
void TraceClientLinkDll_Init(const char* szTraceLinkName, int charType)
{
    CTraceClientLink::CreateInstance(szTraceLinkName, (CTraceClientLink::ECharType)charType);
}

void  TraceClientLinkDll_Release()
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
void CTraceClientLink::CreateDllInstance(void* pModule, const char* szTraceLinkName, CTraceClientLink::ECharType charType)
{
   typedef void (*TraceClientLinkDll_InitProc)(const char* szTraceLinkName, int);

   TraceClientLinkDll_InitProc         InitProc = (TraceClientLinkDll_InitProc)dlsym(pModule, "_TraceClientLinkDll_Init");

   if ( NULL == InitProc )
        InitProc = (TraceClientLinkDll_InitProc)dlsym(pModule, "TraceClientLinkDll_Init");

   if ( InitProc != NULL )
      InitProc(szTraceLinkName, charType);
}


/**
 *
 */
void CTraceClientLink::ReleaseDllInstance(void* pModule)
{
   typedef void (*TraceClientLinkDll_ReleaseProc)();

   TraceClientLinkDll_ReleaseProc         ReleaseProc = (TraceClientLinkDll_ReleaseProc)dlsym(pModule, "_TraceClientLinkDll_Release");

   if ( ReleaseProc != NULL )
      ReleaseProc();
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
m_pModule(NULL),
m_pfctInitModule(NULL),
m_pfctTerminateModule(NULL),
m_pfctCreateTraceLink(NULL),
m_pfctReleaseTraceLink(NULL),
m_pfctWriteTraceA(NULL),
m_pfctWriteTraceW(NULL),
m_id(0)
{
    m_pModule = dlopen("./libTraceClientLink.dylib", RTLD_NOW);
	if ( m_pModule )
	{
        m_pfctInitModule = (PFCTInitModule)dlsym(m_pModule, "InitModule");
        m_pfctTerminateModule = (PFCTTerminateModule)dlsym(m_pModule, "TerminateModule");
        m_pfctCreateTraceLink = (PFCTCreateTraceLink)dlsym(m_pModule, "CreateTraceLink");
		m_pfctReleaseTraceLink = (PFCTReleaseTraceLink)dlsym(m_pModule, "ReleaseTraceLink");
		m_pfctWriteTraceA = (PFCTWriteTraceA)dlsym(m_pModule, "WriteTraceA");
		m_pfctWriteTraceW = (PFCTWriteTraceW)dlsym(m_pModule, "WriteTraceW");
	}

    m_pfctInitModule();

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

	if ( m_pModule )
    {
        m_pfctTerminateModule();
		dlclose(m_pModule);
    }
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
