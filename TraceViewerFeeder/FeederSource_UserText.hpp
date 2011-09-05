#ifndef FEEDERSOURCE_USERTEXT_HPP
#define FEEDERSOURCE_USERTEXT_HPP


#include "FeederSource.hpp"

/**
 *
 */
class CFeederSource_UserText : public CFeederSource
{
public:
    CFeederSource_UserText();
    virtual ~CFeederSource_UserText();

    void SetText( const Nyx::CWString& text );
    void SetText( const wchar_t* wszText );

    virtual void GetLine( Nyx::CWString& line );

protected:

    Nyx::CWString               m_Text;
    unsigned int                m_Index;
    Nyx::CStringFormaterRef     m_refStringFormater;
};

#endif // FEEDERSOURCE_USERTEXT_HPP
