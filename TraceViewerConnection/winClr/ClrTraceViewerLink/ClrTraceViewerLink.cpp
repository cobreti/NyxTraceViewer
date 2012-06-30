// ClrTraceViewerLink.cpp : Defines the entry point for the DLL application.
//

#include <Windows.h>
#include "ClrTraceViewerLink.hpp"
#include "TraceClientLink.hpp"


#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif


using namespace System;

/**
 *
 */
void CClrTraceViewerLink::Write( System::String^ text )
{
    System::Text::Encoding^     WideCharEncoder = System::Text::Encoding::Unicode;
    array<unsigned char>^       WideCharString = WideCharEncoder->GetBytes(text);
    pin_ptr<unsigned char>      wszText = &WideCharString[0];

    CTraceClientLink::Instance().Write((wchar_t*)wszText);
}

/**
 *
 */
CClrTraceViewerLink::CClrTraceViewerLink(System::String^ ModuleName)
{
    System::Text::Encoding^     AsciiEncoder = System::Text::Encoding::ASCII;
    array<unsigned char>^       AsciiString = AsciiEncoder->GetBytes(ModuleName);
    pin_ptr<unsigned char>      szName = &AsciiString[0];

    CTraceClientLink::CreateInstance((const char*)szName, CTraceClientLink::eCT_WideChar);
}

/**
 *
 */
CClrTraceViewerLink::!CClrTraceViewerLink()
{
    CTraceClientLink::ReleaseInstance();
}
