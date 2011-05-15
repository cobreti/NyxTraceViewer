#ifndef _TRACESCOLLECTION_HPP_
#define _TRACESCOLLECTION_HPP_


#include <list>

namespace TraceClientCore
{
    class CTraceData;


    class CTracesCollection : public std::list<CTraceData*>
    {
        typedef     std::list<CTraceData>           BaseType;

    public:
        CTracesCollection();
        virtual ~CTracesCollection();

    protected:
    };
}


#endif // _TRACESCOLLECTION_HPP_
