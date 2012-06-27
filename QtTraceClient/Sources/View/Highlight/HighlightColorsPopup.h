#ifndef _HIGHLIGHTCOLORSPOPUP_H_
#define _HIGHLIGHTCOLORSPOPUP_H_

#include <QWidget>

namespace Ui
{
    class HighlightColorsPopup;
}

class CHighlightBrushesSet;
class CHighlightBrush;
class CColorBtn;
class CHighlightBrushBtn;


/**
 *
 */
class CHighlightColorsPopup : public QWidget
{
    Q_OBJECT

public:
    CHighlightColorsPopup();
    virtual ~CHighlightColorsPopup();

    void Show(const QPoint& pt, const CHighlightBrushesSet& BrushesSet);

signals:

    //void OnChooseColor( const QColor& color );
    void OnChooseBrush( CHighlightBrush* pBrush );

public slots:

    void OnBrushSelected(CHighlightBrushBtn* pBtn);

protected:

    Ui::HighlightColorsPopup*       ui;
};


#endif // _HIGHLIGHTCOLORSPOPUP_H_

