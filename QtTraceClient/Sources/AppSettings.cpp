#include "AppSettings.hpp"
#include "View/ViewColumnSettings.hpp"

/**
 *
 */
CAppSettings::CAppSettings() :
    m_ClientId(0)
{
    Init();
}


/**
 *
 */
CAppSettings::~CAppSettings()
{
}


/**
 *
 */
void CAppSettings::Init()
{
    CViewColumnSettings*		pColSettings = NULL;

    // Line number
    pColSettings = new CViewColumnSettings();
    pColSettings->SetWidth(0);
    pColSettings->Margins() = CViewItemMargins(10, 0, 10, 0);
    pColSettings->AutoWidth() = true;
//    pColSettings->SetPainterId( CViewItemPainter::ePId_LineNumber );
    pColSettings->SetTitle("Line #");
//    pColSettings->SetWidth( TextMetrics.boundingRect(pColSettings->GetTitle()).width() + pColSettings->Margins().width());
    m_DefaultViewSettings.ColumnsSettings().Set( eVCI_LineNumber, pColSettings );

    // Module name
    pColSettings = new CViewColumnSettings();
    pColSettings->SetWidth(0);
    pColSettings->Margins() = CViewItemMargins(10, 0, 10, 0);
    pColSettings->AutoWidth() = true;
//    pColSettings->SetPainterId( CViewItemPainter::ePId_ModuleName );
    pColSettings->SetTitle("Module Name");
//    pColSettings->SetWidth( TextMetrics.boundingRect(pColSettings->GetTitle()).width() + pColSettings->Margins().width());
    m_DefaultViewSettings.ColumnsSettings().Set( eVCI_ModuleName, pColSettings );

    // TickCount
    pColSettings = new CViewColumnSettings();
    pColSettings->SetWidth(0);
    pColSettings->Margins() = CViewItemMargins(10, 0, 10, 0);
    pColSettings->AutoWidth() = true;
//    pColSettings->SetPainterId( CViewItemPainter::ePId_TickCount );
    pColSettings->SetTitle("Time Stamp");
//    pColSettings->SetWidth( TextMetrics.boundingRect(pColSettings->GetTitle()).width() + pColSettings->Margins().width());
    m_DefaultViewSettings.ColumnsSettings().Set( eVCI_TickCount, pColSettings );

    // ThreadId
    pColSettings = new CViewColumnSettings();
    pColSettings->SetWidth(0);
    pColSettings->Margins() = CViewItemMargins(10, 0, 10, 0);
    pColSettings->AutoWidth() = true;
//    pColSettings->SetPainterId( CViewItemPainter::ePId_ThreadId );
    pColSettings->SetTitle("Thread Id");
//    pColSettings->SetWidth( TextMetrics.boundingRect(pColSettings->GetTitle()).width() + pColSettings->Margins().width());
    m_DefaultViewSettings.ColumnsSettings().Set( eVCI_ThreadId, pColSettings );

    // data
    pColSettings = new CViewColumnSettings();
    pColSettings->SetWidth(0);
    pColSettings->Margins() = CViewItemMargins(10, 0, 20, 0);
    pColSettings->AutoWidth() = true;
//    pColSettings->SetPainterId( CViewItemPainter::ePId_Data );
    pColSettings->SetTitle("Data");
//    pColSettings->SetWidth( TextMetrics.boundingRect(pColSettings->GetTitle()).width() + pColSettings->Margins().width());
    m_DefaultViewSettings.ColumnsSettings().Set( eVCI_Data, pColSettings );
}
