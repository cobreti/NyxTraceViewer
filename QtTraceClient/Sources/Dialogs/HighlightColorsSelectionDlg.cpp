#include "HighlightColorsSelectionDlg.h"

#include "ui_HighlightColorsSelectionDlg.h"
#include "View/Highlight/ViewHighlightSettings.hpp"
#include "View/Highlight/HighlightBrush.hpp"
#include "Color/ColorBtn.h"


/**
 *
 */
CHighlightColorsSelectionDlg::CHighlightColorsSelectionDlg(CViewHighlightSettings& rSettings, QWidget* parent) : QDialog(parent),
    ui(new Ui::HighlightColorsSelectionDlg),
    m_rSettings(rSettings)
{
    ui->setupUi(this);

    Init();

    connect( ui->CloseBtn, SIGNAL(clicked()), this, SLOT(OnClose()));
}


/**
 *
 */
CHighlightColorsSelectionDlg::~CHighlightColorsSelectionDlg()
{
}


/**
 *
 */
void CHighlightColorsSelectionDlg::OnClose()
{
    close();
}


/**
 *
 */
void CHighlightColorsSelectionDlg::OnHighlightColorChanged( CColorBtn* pBtn )
{
    UpdateSettings();
}


/**
 *
 */
void CHighlightColorsSelectionDlg::Init()
{
    InitFrame( *ui->WordHighlightsFrame, m_WordHighlightColorButtons, m_rSettings.WordHighlights() );
    InitFrame( *ui->LineHighlightFrame, m_LineHighlightColorButtons, m_rSettings.LineHighlights() );
}


/**
 *
 */
void CHighlightColorsSelectionDlg::InitFrame( QFrame& rFrame, ColorButtonsTable& ButtonsTable, const CHighlightBrushesSet& brushes )
{
    size_t      count = brushes.Size();
    bool        bRet;

    ButtonsTable.resize(count);

    for (size_t index = 0; index < count; ++index)
    {
        CColorBtn*      pBtn = new CChooseColorBtn();
        ButtonsTable[index] = pBtn;
        pBtn->Color() = brushes[index]->Color();
        rFrame.layout()->addWidget(pBtn);

        bRet = connect( pBtn, SIGNAL(OnColorChanged(CColorBtn*)), this, SLOT(OnHighlightColorChanged(CColorBtn*)));
    }
}


/**
 *
 */
void CHighlightColorsSelectionDlg::UpdateSettings()
{
    for (size_t index = 0; index < m_WordHighlightColorButtons.size(); ++index)
        m_rSettings.WordHighlights()[index]->SetColor( m_WordHighlightColorButtons[index]->Color() );

    for (size_t index = 0; index < m_LineHighlightColorButtons.size(); ++index)
        m_rSettings.LineHighlights()[index]->SetColor( m_LineHighlightColorButtons[index]->Color() );
}
