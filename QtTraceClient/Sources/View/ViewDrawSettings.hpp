#ifndef VIEWDRAWSETTINGS_HPP
#define VIEWDRAWSETTINGS_HPP


#include <Nyx.hpp>
#include <vector>
#include "ViewItemPainter.hpp"



/**
 *
 */
class CViewDrawSettings
{
public:
    CViewDrawSettings();
    ~CViewDrawSettings();

    CViewItemPainter*       Painter (const CViewItemPainter::EPainterId& id) const       { return m_Painters[id]; }
    CViewItemPainter*&      Painter (const CViewItemPainter::EPainterId& id)             { return m_Painters[id]; }

    float SingleLineHeight() const      { return m_LineHeight; }
    void setSingleLineHeight(float height);

    void CalculateLineHeight();

protected:

    typedef     std::vector<CViewItemPainter*>      TPaintersArray;


protected:

    TPaintersArray      m_Painters;
    float               m_LineHeight;
};


#endif // VIEWDRAWSETTINGS_HPP
