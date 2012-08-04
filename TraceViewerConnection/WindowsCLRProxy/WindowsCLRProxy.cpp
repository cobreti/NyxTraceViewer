// This is the main DLL file.

using namespace System::Runtime::InteropServices;

#include "WindowsCLRProxy.h"
#include <NyxTraceViewerConnection.hpp>
#include <vcclr.h>


namespace NyxTraceViewer
{
	/**
	 *
	 */
	void ClrConnection::ReleaseInstance()
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
	void ClrConnection::CreateInstance( System::String^ name )
	{
		s_Instance = gcnew ClrConnection(name);
	}


	/**
	 *
	 */
	ClrConnection^ ClrConnection::Instance()
	{
		return s_Instance;
	}


	/**
	 *
	 */
	ClrConnection::ClrConnection( System::String^ name )
	{
		IntPtr p = Marshal::StringToHGlobalAnsi(name);
		//pin_ptr<const char>	inner_str = &(name->ToCharArray()[0]);

		Nyx::CTraceViewerConnection_Pipe_WChar::CreateInstance((const char*)(void*)p);

		Marshal::FreeHGlobal(p);
	}
	


	/**
	 *
	 */
	ClrConnection::!ClrConnection()
	{
		Nyx::CTraceViewerConnection::ReleaseInstance();
	}


	/**
	 *
	 */
	ClrConnection::~ClrConnection()
	{
	}


	/**
	 *
	 */
	void ClrConnection::Write( System::String^ text )
	{
		int id = System::Threading::Thread::CurrentThread->ManagedThreadId;
		int sysid = System::AppDomain::GetCurrentThreadId();

		pin_ptr<const wchar_t>	wszText = PtrToStringChars(text);
		Nyx::CTraceViewerConnection::Instance().WriteWithThreadId(sysid, id, wszText);
	}
}

