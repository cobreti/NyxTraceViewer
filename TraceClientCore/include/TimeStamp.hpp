#ifndef _TIMESTAMP_HPP_
#define _TIMESTAMP_HPP_

#include <Nyx.hpp>


namespace TraceClientCore
{
    /**
     *
     */
    class CTimeStamp
    {
    public:

        enum EInputType
        {
            eIT_Milliseconds,
            eIT_Microseconds
        };

    public:
        CTimeStamp();
        CTimeStamp(const CTimeStamp& timestamp);
        CTimeStamp(const Nyx::UInt64 value, const EInputType& inputType);
        ~CTimeStamp();

        const CTimeStamp& operator = (const CTimeStamp& timestamp);

        void ToString( Nyx::CWString& str );

    protected:

        Nyx::UInt64     m_MicroSeconds;

    };
}


#endif // _TIMESTAMP_HPP_
