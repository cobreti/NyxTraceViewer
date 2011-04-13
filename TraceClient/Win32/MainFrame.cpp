#include "StdAfx.h"

#include <Nyx.hpp>

#include "MainFrame.h"
#include "TracesWnd.h"

//------------------
//	FOR TEST ONLY

#include "AppCoreServices.hpp"
#include "TraceDataRepos.hpp"
#include "TraceDataReposIterator.hpp"
#include "Dummy_TraceFeeder.hpp"
#include "TraceDataReposFeederLink.hpp"

//	FOR TEST ONLY
//------------------

/**
 *
 */
void CMainFrame::CreateMainMenu()
{
	MenuStrip^					MenuBar = gcnew MenuStrip();

	MenuBar->Items->Add( CreateFileMenu() );
	MenuBar->Items->Add( gcnew ToolStripSeparator() );
	MenuBar->Items->Add( CreateTestMenu() );

	MenuBar->MenuDeactivate += gcnew System::EventHandler(this, &CMainFrame::OnMenuDeactivated);

	this->MainMenuStrip = MenuBar;
	this->Controls->Add(MenuBar);
}


/**
 *
 */
ToolStripMenuItem^ CMainFrame::CreateFileMenu()
{
	ToolStripMenuItem^			FileMenuItem = gcnew ToolStripMenuItem("File");
	ToolStripDropDownMenu^		FileDropDown = gcnew ToolStripDropDownMenu();

	FileMenuItem->DropDown = FileDropDown;
	FileDropDown->Items->Add("New", nullptr, gcnew EventHandler(this, &CMainFrame::OnNew) );
	FileDropDown->Items->Add( gcnew ToolStripSeparator() );

	FileDropDown->Closed += gcnew ToolStripDropDownClosedEventHandler(this, &CMainFrame::OnDropDownClosed);

	return FileMenuItem;
}


/** 
 *
 */
ToolStripMenuItem^ CMainFrame::CreateTestMenu()
{
	ToolStripMenuItem^			TestMenuItem = gcnew ToolStripMenuItem("Test");
	ToolStripDropDownMenu^		TestDropDown = gcnew ToolStripDropDownMenu();

	TestMenuItem->DropDown = TestDropDown;
	TestDropDown->Items->Add("Insert trace data", nullptr, gcnew EventHandler(this, &CMainFrame::OnTestInsertTraceData) );
	TestDropDown->Items->Add("Enum trace data", nullptr, gcnew EventHandler(this, &CMainFrame::OnTestEnumTraceData) );
	TestDropDown->Items->Add("Update UI Repos", nullptr, gcnew EventHandler(this, &CMainFrame::OnTestUpdateUIRepos) );
	TestDropDown->Items->Add("create dummy feeder", nullptr, gcnew EventHandler(this, &CMainFrame::OnTestCreateDummyFeeder) );

	TestDropDown->Closed += gcnew ToolStripDropDownClosedEventHandler(this, &CMainFrame::OnDropDownClosed);

	return TestMenuItem;
}


/**
 *
 */
void CMainFrame::OnNew( Object^ Sender, EventArgs^ Args )
{
	CTracesWnd^		Wnd = gcnew CTracesWnd();

	Wnd->MdiParent = this;
	Wnd->Show();
}


/**
 *
 */
void CMainFrame::OnMenuDeactivated( Object^ Sender, EventArgs^ Args )
{
	System::GC::Collect();
}


/**
 *
 */
void CMainFrame::OnDropDownClosed( Object^ Sender, ToolStripDropDownClosedEventArgs^ args )
{
	System::GC::Collect();
}


/**
 *
 */
void CMainFrame::OnTestInsertTraceData(System::Object ^Sender, System::EventArgs ^Args)
{
	CTraceDataRepos&				rRepos = CAppCoreServices::Instance().TracesPools()[L"Default"]->TraceRepository();
	CTraceDataReposIterator*		pIter = NULL;
	CTraceDataRef					refTraceData;
	size_t							SizeToInsert(14);
	size_t							Index = 0;
	Nyx::CStringFormaterRef			refStringFormater = Nyx::CStringFormater::Alloc(1024);
	const wchar_t*					wszBuffer = NULL;

	CTraceDataRepos::Accessor		TDReposAccessor(rRepos);

	while ( Index < SizeToInsert )
	{
		refTraceData = new CTraceData();

		refStringFormater->Format(L"%08X", Index + m_LastTraceIndex );
		refTraceData->ThreadId() = Nyx::CString::Alloc(refStringFormater->GetBuffer());

		refStringFormater->Format(L"%i", Index + m_LastTraceIndex);
		refTraceData->TickCount() = Nyx::CString::Alloc(refStringFormater->GetBuffer());

		refStringFormater->Format(L"Trace data test for index %i", Index + m_LastTraceIndex );
		refTraceData->Data() = Nyx::CString::Alloc(refStringFormater->GetBuffer());

		TDReposAccessor->Add(refTraceData);

		Nyx::CTraceStream(0x0) << Nyx::CTF_Text(L"Adding : ") << Nyx::CTF_Text( refTraceData->Data()->CStr() );

		++ Index;
	}

	m_LastTraceIndex += SizeToInsert;

	size_t Size = TDReposAccessor->Count();

	if ( pIter != NULL )
	{
		delete pIter;
		pIter = NULL;
	}
}


/**
 *
 */
void CMainFrame::OnTestEnumTraceData(System::Object ^Sender, System::EventArgs ^Args)
{
	int Index = 0;
	while ( Index < this->MdiChildren->GetLength(0) )
	{
		CTracesWnd^	pTracesWnd = (CTracesWnd^) this->MdiChildren->GetValue(Index);

		if ( pTracesWnd != nullptr )
			pTracesWnd->OnTest_EnumTraceData();

		++ Index;
	}
}


/**
 *
 */
void CMainFrame::OnTestUpdateUIRepos( Object^ Sender, EventArgs^ Args )
{
	int Index = 0;
	while ( Index < this->MdiChildren->GetLength(0) )
	{
		CTracesWnd^	pTracesWnd = (CTracesWnd^) this->MdiChildren->GetValue(Index);

		if ( pTracesWnd != nullptr )
			pTracesWnd->OnTest_UpdateUIRepos();

		++ Index;
	}
}


/**
 *
 */
void CMainFrame::OnTestCreateDummyFeeder( Object^ Sender, EventArgs^ Args )
{
	CTraceDataRepos&			rRepos = CAppCoreServices::Instance().TracesPools()[L"Default"]->TraceRepository();
	CTracesFeeder*				pFeeder = new CDummy_TraceFeeder(L"DummyFeeder");
	CTracesFeeder::Accessor		FeederAccess(*pFeeder);

	FeederAccess->FeederLinks().Add( new CTraceDataReposFeederLink(rRepos) );

	CAppCoreServices::Instance().Feeders().Add(pFeeder);
}
