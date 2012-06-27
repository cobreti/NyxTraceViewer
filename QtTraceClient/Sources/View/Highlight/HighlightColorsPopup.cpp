#include "HighlightColorsPopup.h"
#include "HighlightBrushesSet.hpp"
#include "HighlightBrush.hpp"
#include "Color/ColorBtn.h"

#include "ui_HighlightColorsPopup.h"

#include <QHBoxLayout>


/**
 *
 */
CHighlightColorsPopup::CHighlightColorsPopup() : QWidget(),
    ui(new Ui::HighlightColorsPopup)
{
    ui->setupUi(this);

    setLayout(new QHBoxLayout());
}


/**
 *
 */
CHighlightColorsPopup::~CHighlightColorsPopup()
{
}


/**
 *
 */
void CHighlightColorsPopup::Show(const QPoint& pt, const CHighlightBrushesSet& BrushesSet)
{
    for (size_t index = 0; index < BrushesSet.Size(); ++index)
    {
        CHighlightBrushBtn*  pBtn = new CHighlightBrushBtn();
        pBtn->SetBrush( BrushesSet[index] );
        //pBtn->Color() = BrushesSet[index]->Color();
        layout()->addWidget(pBtn);

        connect( pBtn, SIGNAL(OnBrushSelected(CHighlightBrushBtn*)), this, SLOT(OnBrushSelected(CHighlightBrushBtn*)));
    }

    setWindowFlags(Qt::Popup);

    move(pt);
    show();
}


/**
 *
 */
void CHighlightColorsPopup::OnBrushSelected(CHighlightBrushBtn* pBtn)
{
    emit OnChooseBrush(pBtn->Brush());
    close();
}
