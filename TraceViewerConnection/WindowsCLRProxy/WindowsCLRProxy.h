// WindowsCLRProxy.h

#pragma once

using namespace System;

namespace NyxTraceViewer 
{

	public ref class ClrConnection
	{
	public:

		static void CreateInstance( System::String^ name );
		static void ReleaseInstance();
        static ClrConnection^ Instance();

		ClrConnection( System::String^ name );
		!ClrConnection();
		~ClrConnection();

		virtual void Write( System::String^ text );

	private:
		
		static ClrConnection^ s_Instance = nullptr;
	};
}
