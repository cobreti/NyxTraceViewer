#include "TimeStamp.hpp"


namespace TraceClientCore
{
    /**
     *
     */
    CTimeStamp::CTimeStamp() : 
    m_MicroSeconds(0)
    {
    }


    /**
     *
     */
    CTimeStamp::CTimeStamp(const CTimeStamp& timestamp) :
    m_MicroSeconds(timestamp.m_MicroSeconds)
    {
    }


    /**
     *
     */
    CTimeStamp::CTimeStamp(const Nyx::UInt64 value, const CTimeStamp::EInputType& inputType) :
    m_MicroSeconds(value)
    {
        if ( inputType == eIT_Milliseconds )
            m_MicroSeconds *= 1000;
    }
    

    /**
     *
     */
    CTimeStamp::~CTimeStamp()
    {
    }


    /**
     *
     */
    const CTimeStamp& CTimeStamp::operator = (const CTimeStamp& timestamp)
    {
        m_MicroSeconds = timestamp.m_MicroSeconds;

        return *this;
    }


    /**
     *
     */
    void CTimeStamp::ToString( Nyx::CWString& str )
    {
        const size_t        kHoursSize = 4;
        const size_t        kMinutesSize = 2;
        const size_t        kSecondsSize = 2;
        const size_t        kMicroSecondsSize = 6;
        const size_t        kSeparatorSize = 1;

        const wchar_t*      kwszSeparator = L":";

        Nyx::UInt64         Seconds = m_MicroSeconds / (1000 * 1000);
        Nyx::UInt64         Microseconds = m_MicroSeconds - Seconds*1000*1000;
        Nyx::UInt64         Minutes = (Seconds / 60) % 60;
        Nyx::UInt64         Hours = (Seconds / 3600) % 24;
        
        Seconds = Seconds % 60;

        Nyx::CWString       Buffer;

        Buffer.Reserve(10);
        str.Reserve( kHoursSize + kMinutesSize + kSecondsSize + kMicroSecondsSize + kSeparatorSize * 3 );

        Buffer.Format(L"%4lu", Hours);
        str = Buffer;
        str += kwszSeparator;

        Buffer.Format( L"%02lu", Minutes );
        str += Buffer;
        str += kwszSeparator;

        Buffer.Format( L"%02lu", Seconds );
        str += Buffer;
        str += kwszSeparator;

        Buffer.Format( L"%lu", Microseconds );
        str += Buffer;
    }

}
