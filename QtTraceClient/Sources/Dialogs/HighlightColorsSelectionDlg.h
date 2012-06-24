#ifndef _HIGHLIGHTCOLORSSELECTIONDLG_H_
#define _HIGHLIGHTCOLORSSELECTIONDLG_H_

#include <QDialog>
#include <vector>

namespace Ui
{
    class HighlightColorsSelectionDlg;
}

class CViewHighlightSettings;
class CHighlightBrushesSet;
class QFrame;
class CColorBtn;



class CHighlightColorsSelectionDlg : public QDialog
{
    Q_OBJECT

public:
    CHighlightColorsSelectionDlg(CViewHighlightSettings& rSettings, QWidget* parent);
    virtual ~CHighlightColorsSelectionDlg();

public slots:

    void OnClose();
    void OnHighlightColorChanged( CColorBtn* pBtn );

protected:

    typedef     std::vector<CColorBtn*>     ColorButtonsTable;

protected:

    void Init();
    void InitFrame( QFrame& rFrame, ColorButtonsTable& ButtonsTable, const CHighlightBrushesSet& brushes );
    void UpdateSettings();

protected:

    Ui::HighlightColorsSelectionDlg*        ui;

    CViewHighlightSettings&                 m_rSettings;

    ColorButtonsTable                       m_WordHighlightColorButtons;
    ColorButtonsTable                       m_LineHighlightColorButtons;
};


#endif // _HIGHLIGHTCOLORSSELECTIONDLG_H_

