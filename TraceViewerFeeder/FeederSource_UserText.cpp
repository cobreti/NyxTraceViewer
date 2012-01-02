#include "FeederSource_UserText.hpp"


/**
 *
 */
CFeederSource_UserText::CFeederSource_UserText() :
    CFeederSource(),
    m_Index(0)
{
    //m_refStringFormater = Nyx::CStringFormater::Alloc(2048);
    m_FormattedLine.Reserve(2048);
}


/**
 *
 */
CFeederSource_UserText::~CFeederSource_UserText()
{
}


/**
 *
 */
void CFeederSource_UserText::SetText( const Nyx::CWString& text )
{
    SetText( text.c_str() );
}


/**
 *
 */
void CFeederSource_UserText::SetText(const wchar_t *wszText)
{
    m_Text = wszText;
    m_Index = 0;
}

/**
 *
 */
void CFeederSource_UserText::GetLine( Nyx::CWString& line )
{
    m_FormattedLine.Format( L" [%i]", ++m_Index );
    line = m_Text;
    line += m_FormattedLine;
}
