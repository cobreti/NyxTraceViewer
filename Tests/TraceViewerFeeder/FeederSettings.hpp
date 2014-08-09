#ifndef _FEEDERSETTINGS_HPP_
#define _FEEDERSETTINGS_HPP_


#include <Nyx.hpp>

class CFeederSource;


/**
 *
 */
class CFeederSettings
{
public:

    enum ETracesAPI
    {
        eTAPI_Unknown,
        eTAPI_NyxPipe,
        eTAPI_NyxTcpIp,
        eTAPI_External,
        eTAPI_Dll,
        eTAPI_PlainTcpIp
    };


public:
    CFeederSettings();
    CFeederSettings(const CFeederSettings& settings);
    virtual ~CFeederSettings();

    const Nyx::CWString&	Name() const    { return m_Name; }
    Nyx::CWString&			Name()          { return m_Name; }

    const Nyx::CWString&	Text() const    { return m_Text; }
    Nyx::CWString&			Text()          { return m_Text; }

    const ETracesAPI&       ApiType() const     { return m_ApiType; }
    ETracesAPI&             ApiType()           { return m_ApiType; }

    const Nyx::UInt32&      TracesPerBlock() const       { return m_TracesPerBlock; }
    Nyx::UInt32&            TracesPerBlock()             { return m_TracesPerBlock; }

    const Nyx::UInt32&      IntervalBetweenBlocks() const       { return m_IntervalBetweenBlocks; }
    Nyx::UInt32&            IntervalBetweenBlocks()             { return m_IntervalBetweenBlocks; }

    CFeederSource*          FeederSource() const                { return m_pFeederSource; }
    CFeederSource*&         FeederSource()                      { return m_pFeederSource; }

    const Nyx::CAString&    TcpIpAddress() const                { return m_TcpIpAddress; }
    Nyx::CAString&          TcpIpAddress()                      { return m_TcpIpAddress; }

    const Nyx::UInt32&      PortNumber() const                  { return m_PortNumber; }
    Nyx::UInt32&            PortNumber()                        { return m_PortNumber; }


    const CFeederSettings& operator = (const CFeederSettings& settings);

protected:

    Nyx::CWString			m_Name;
    Nyx::CWString			m_Text;
    ETracesAPI              m_ApiType;
    Nyx::UInt32             m_TracesPerBlock;
    Nyx::UInt32             m_IntervalBetweenBlocks;
    CFeederSource*          m_pFeederSource;
    Nyx::CAString           m_TcpIpAddress;
    Nyx::UInt32             m_PortNumber;
};


#endif // _FEEDERSETTINGS_HPP_
