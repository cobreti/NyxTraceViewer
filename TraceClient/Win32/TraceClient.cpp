// TraceClient.cpp : main project file.

#include "stdafx.h"

#include <Nyx.hpp>
#include <NyxConsoleTraceOutput.hpp>
#include <NyxAtomicValue.hpp>
#include <NyxNet.hpp>

#include "AppCoreServices.hpp"
#include "UISettings.hpp"
#include "PipeTraceFeeder.hpp"
#include "TraceDataReposFeederLink.hpp"

#include "MainFrame.h"
//#include "Form1.h"

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	Nyx::NyxResult							res;
	Nyx::CModuleRef							refModule = Nyx::CModule::Alloc();
	Nyx::CTraceCompositorRef				refTraceCompositor = Nyx::CTraceCompositor::Alloc();
	NyxNet::CModuleRef						refNetModule = NyxNet::CModule::Alloc();
	Nyx::CAtomicValue						AValue;

	refTraceCompositor->SetOutput( Nyx::CConsoleTraceOutput::Alloc() );

	CAppCoreServicesRef						refAppCoreServices = new CAppCoreServices();
	CUISettings^							pUISettings = gcnew CUISettings();

	res = CAppCoreServices::Instance().Init();
	pUISettings->Init();

	// temporary : add default traces pool
	{
		CTracesPool*	pPool = new CTracesPool(L"Default");
		CAppCoreServices::Instance().TracesPools().Add(pPool);

		CPipeTraceFeeder*		pFeeder = new CPipeTraceFeeder(L"Default");

		CAppCoreServices::Instance().Feeders().Add(pFeeder);

		CTraceDataReposFeederLink*	pFeederLink = new CTraceDataReposFeederLink(pPool->TraceRepository());

		{
			CPipeTraceFeeder::Accessor		FeederAccess(*pFeeder);

			if (FeederAccess)
				FeederAccess->FeederLinks().Add(pFeederLink);
		}
	}

	if ( Nyx::Succeeded(res) )
	{
		// Enabling Windows XP visual effects before any controls are created
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false); 

		// Create the main window and run it
		Application::Run(gcnew CMainFrame());

		pUISettings->Terminate();
		CAppCoreServices::Instance().Terminate();
	}
	else
	{
		Nyx::CTraceStream(0x0).Write(L"application core services initialization failure" );
	}

	return 0;
}
