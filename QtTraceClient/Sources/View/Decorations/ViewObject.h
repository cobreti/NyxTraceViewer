#ifndef VIEWOBJECT_H
#define VIEWOBJECT_H

#include <Nyx.hpp>


class CViewObject : public Nyx::CRefCount_Impl<>
{
public:
    CViewObject();
    virtual ~CViewObject();
};


#endif // VIEWOBJECT_H
