// This is the main DLL file.

using namespace System::Runtime::InteropServices;

#include "WindowsCLRProxy.h"
#include <NyxTraceViewerConnection.hpp>
#include <vcclr.h>


namespace TraceViewerProxy
{
	/**
	 *
	 */
	void TraceViewerConnection::ReleaseInstance()
	{
		if ( s_Instance != nullptr )
		{
			delete s_Instance;
			s_Instance = nullptr;
		}
	}


	/**
	 *
	 */
	void TraceViewerConnection::CreateInstance( System::String^ name )
	{
		s_Instance = gcnew TraceViewerConnection(name);
	}


	/**
	 *
	 */
	TraceViewerConnection^ TraceViewerConnection::Instance()
	{
		return s_Instance;
	}


	/**
	 *
	 */
	TraceViewerConnection::TraceViewerConnection( System::String^ name )
	{
		IntPtr p = Marshal::StringToHGlobalAnsi(name);
		//pin_ptr<const char>	inner_str = &(name->ToCharArray()[0]);

		Nyx::CTraceViewerConnection_Pipe_WChar::CreateInstance((const char*)(void*)p);

		Marshal::FreeHGlobal(p);
	}
	


	/**
	 *
	 */
	TraceViewerConnection::!TraceViewerConnection()
	{
		Nyx::CTraceViewerConnection::ReleaseInstance();
	}


	/**
	 *
	 */
	TraceViewerConnection::~TraceViewerConnection()
	{
	}


	/**
	 *
	 */
	void TraceViewerConnection::Write( System::String^ text )
	{
		pin_ptr<const wchar_t>	wszText = PtrToStringChars(text);
		Nyx::CTraceViewerConnection::Instance().Write(wszText);
	}
}

