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

extern "C" __declspec( dllexport ) unsigned int CreateTraceLink( const char* szName, int nType );
extern "C" __declspec( dllexport ) void ReleaseTraceLink( const unsigned int& id );
extern "C" __declspec( dllexport ) void WriteTraceA( const unsigned int& id, const char* szData, va_list args );
extern "C" __declspec( dllexport ) void WriteTraceW( const unsigned int& id, const wchar_t* wszData, va_list args );