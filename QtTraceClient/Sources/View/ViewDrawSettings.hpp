#ifndef VIEWDRAWSETTINGS_HPP
#define VIEWDRAWSETTINGS_HPP


#include <Nyx.hpp>
#include <vector>



/**
 *
 */
class CViewDrawSettings
{
public:
    CViewDrawSettings();
    ~CViewDrawSettings();

    float SingleLineHeight() const      { return m_LineHeight; }
    void setSingleLineHeight(float height);

    void CalculateLineHeight();

protected:


protected:

    float               m_LineHeight;
};


#endif // VIEWDRAWSETTINGS_HPP
