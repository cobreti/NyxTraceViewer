#include <Windows.h>

#include "TracesViewSettings.hpp"
#include "TraceDataItemDisplay.hpp"
#include "TraceTickCountItemDisplay.hpp"
#include "TraceThreadIdItemDisplay.hpp"



/**
 *
 */
CTracesViewSettings::CTracesViewSettings()
{
}


/**
 *
 */
CTracesViewSettings::~CTracesViewSettings()
{
}


/**
 *
 */
void CTracesViewSettings::Init()
{
	DWORD		dwBkColor = ::GetSysColor(COLOR_WINDOW);
	Color		BkColor = Color::FromArgb( GetRValue(dwBkColor), GetGValue(dwBkColor), GetBValue(dwBkColor) );

	m_BackgroundBrush = gcnew SolidBrush(BkColor);

	m_Columns = gcnew CTracesViewColumnsArray();

	CreateColumn_TickCount();
	CreateColumn_ThreadId();
	CreateColumn_TraceData();
}


/**
 *
 */
void CTracesViewSettings::Terminate()
{
	delete m_BackgroundBrush;
}


/**
 *
 */
void CTracesViewSettings::CreateColumn_TraceData()
{
	CTracesViewColumnSettings^		Settings = gcnew CTracesViewColumnSettings();

	Settings->ID = ETracesViewColumnID::TraceData;
	Settings->Width = -1;
	Settings->Font = gcnew Font("Arial", 10, FontStyle::Regular);
	Settings->ItemDisplay = gcnew CTraceDataItemDisplay();
	Settings->Margins.Left = 20;
	Settings->Margins.Right = 20;
	//Settings->Margins.Top = 10;
	//Settings->Margins.Bottom = 10;

	m_Columns->Item[2] = Settings;
}



/**
 *
 */
void CTracesViewSettings::CreateColumn_ThreadId()
{
	CTracesViewColumnSettings^		Settings = gcnew CTracesViewColumnSettings();

	Settings->ID = ETracesViewColumnID::ThreadID;
	Settings->Width = 100;
	//Settings->Margins.Top = 10;
	//Settings->Margins.Bottom = 10;
	Settings->Margins.Left = 10;
	Settings->Margins.Right = 10;
	Settings->Font = gcnew Font("Arial", 10, FontStyle::Regular);
	Settings->ItemDisplay = gcnew CTraceThreadIdItemDisplay();

	m_Columns->Item[1] = Settings;
}


/**
 *
 */
void CTracesViewSettings::CreateColumn_TickCount()
{
	CTracesViewColumnSettings^		Settings = gcnew CTracesViewColumnSettings();

	Settings->ID = ETracesViewColumnID::TickCount;
	Settings->Width = 100;
	Settings->Margins.Left = 10;
	Settings->Margins.Right = 10;
	//Settings->Margins.Top = 10;
	//Settings->Margins.Bottom = 10;
	Settings->Font = gcnew Font("Arial", 10, FontStyle::Regular);
	Settings->ItemDisplay = gcnew CTraceTickCountItemDisplay();

	m_Columns->Item[0] = Settings;
}
