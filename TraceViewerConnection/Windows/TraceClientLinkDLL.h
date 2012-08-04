// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TRACECLIENTLINK_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// TRACECLIENTLINK_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TRACECLIENTLINK_EXPORTS
#define TRACECLIENTLINK_API __declspec(dllexport)
#else
#define TRACECLIENTLINK_API __declspec(dllimport)
#endif

extern "C" __declspec( dllexport ) unsigned int __cdecl CreateTraceLink_PipeAnsi( const char* szName );
extern "C" __declspec( dllexport ) unsigned int __cdecl CreateTraceLink_PipeWChar( const char* szName );
extern "C" __declspec( dllexport ) unsigned int __cdecl CreateTraceLink_TcpAnsi( const char* szName, const char* szAddr );
extern "C" __declspec( dllexport ) unsigned int __cdecl CreateTraceLink_TcpWChar( const char* szName, const char* szAddr );
extern "C" __declspec( dllexport ) void __cdecl ReleaseTraceLink( const unsigned int& id );
extern "C" __declspec( dllexport ) void __cdecl WriteTraceA( const unsigned int& id, const char* szData, va_list args );
extern "C" __declspec( dllexport ) void __cdecl WriteTraceW( const unsigned int& id, const wchar_t* wszData, va_list args );
extern "C" __declspec( dllexport ) void __cdecl WriteTraceW_WithThreadId(	const unsigned int& id,
																			const unsigned int& threadid,
																			const unsigned int& mthreadid,
																			const wchar_t* wszData, va_list args );