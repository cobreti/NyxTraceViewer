#ifndef FEEDERSOURCE_TEXTFILE_HPP
#define FEEDERSOURCE_TEXTFILE_HPP

#include "FeederSource.hpp"

/**
 *
 */
class CFeederSource_TextFile : public CFeederSource
{
public:
    CFeederSource_TextFile();
    virtual ~CFeederSource_TextFile();

    void SetFile( const char* szFilename );

    virtual void GetLine( Nyx::CWString& line );

protected:

    typedef     std::list<Nyx::CAString>        TTextRows;

protected:

    TTextRows                   m_Rows;
    TTextRows::const_iterator   m_CurrentPos;
};

#endif // FEEDERSOURCE_TEXTFILE_HPP
