#ifndef _HIGHLIGHTBRUSHESSET_HPP_
#define _HIGHLIGHTBRUSHESSET_HPP_

#include <Nyx.hpp>

#include <vector>


class CHighlightBrush;


/**
 *
 */
class CHighlightBrushesSet
{
public:
    CHighlightBrushesSet();
    virtual ~CHighlightBrushesSet();

    const size_t Size() const       { return m_Brushes.size(); }

    CHighlightBrush* operator [] (const size_t& index) const      { return m_Brushes[index]; }

protected:

    typedef     std::vector<CHighlightBrush*>       BrushesVector;

protected:

    BrushesVector       m_Brushes;
};


#endif // _HIGHLIGHTBRUSHESSET_HPP_
