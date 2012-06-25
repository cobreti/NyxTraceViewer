#ifndef _HIGHLIGHTCOLORSPOPUP_H_
#define _HIGHLIGHTCOLORSPOPUP_H_

#include <QWidget>

namespace Ui
{
    class HighlightColorsPopup;
}

class CHighlightBrushesSet;
class CColorBtn;

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

    void OnChooseColor( const QColor& color );

public slots:

    void OnColorSelected(CColorBtn* pBtn);

protected:

    Ui::HighlightColorsPopup*       ui;
};


#endif // _HIGHLIGHTCOLORSPOPUP_H_

