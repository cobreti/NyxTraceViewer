// WindowsCLRProxy.h

#pragma once

using namespace System;

namespace TraceViewerProxy 
{

	public ref class TraceViewerConnection
	{
	public:

		static void CreateInstance( System::String^ name );
		static void ReleaseInstance();
        static TraceViewerConnection^ Instance();

		TraceViewerConnection( System::String^ name );
		!TraceViewerConnection();
		~TraceViewerConnection();

		virtual void Write( System::String^ text );

	private:
		
		static TraceViewerConnection^ s_Instance = nullptr;
	};
}
