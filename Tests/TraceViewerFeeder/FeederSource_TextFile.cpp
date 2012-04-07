#include "FeederSource_TextFile.hpp"

#include <NyxAnsiFile.hpp>

/**
 *
 */
CFeederSource_TextFile::CFeederSource_TextFile() :
    CFeederSource()
{
}


/**
 *
 */
CFeederSource_TextFile::~CFeederSource_TextFile()
{
}


/**
 *
 */
void CFeederSource_TextFile::SetFile( const char* szFilename )
{
    m_Rows.clear();

    Nyx::CAnsiFileRef           refFile = Nyx::CAnsiFile::Alloc();
    Nyx::NyxResult              res;
    Nyx::CAString               line;

    res = refFile->Open( szFilename );
    if ( Nyx::Succeeded(res) )
    {
        while ( Succeeded(res) )
        {
            res = refFile->Read(line);
            if ( Succeeded(res) )
            {
                m_Rows.push_back(line);
//                Nyx::CTraceStream(0x0)
//                        << Nyx::CTF_AnsiText(line.c_str());
            }
        }

        refFile->Close();
    }

    m_CurrentPos = m_Rows.begin();
}


/**
 *
 */
void CFeederSource_TextFile::GetLine( Nyx::CWString& line )
{
    if ( m_Rows.empty() || m_CurrentPos == m_Rows.end() )
        return;

    line = *m_CurrentPos;

    ++ m_CurrentPos;

    if ( m_CurrentPos == m_Rows.end() )
        m_CurrentPos = m_Rows.begin();
}

