#ifndef FEEDERSOURCE_HPP
#define FEEDERSOURCE_HPP


#include <Nyx.hpp>


/**
 *
 */
class CFeederSource
{
public:
    CFeederSource();
    virtual ~CFeederSource();

    virtual void GetLine( Nyx::CWString& line ) = 0;
};

#endif // FEEDERSOURCE_HPP
