#ifndef _VIEWITEMPATTERN_HPP_
#define _VIEWITEMPATTERN_HPP_

#include <Nyx.hpp>
#include <NyxRange.hpp>

#include <QString>


DECLARE_OBJECTREF(CViewItemPattern);

/**
 *
 */
class CViewItemPattern : public Nyx::CRefCount_Impl<>
{
public:
    CViewItemPattern();

    virtual Nyx::CRange Match( const QString& text, const long& startIndex ) = 0;
    virtual int PatternLength() const = 0;

protected:
    virtual ~CViewItemPattern();
};




#endif // _VIEWITEMPATTERN_HPP_
