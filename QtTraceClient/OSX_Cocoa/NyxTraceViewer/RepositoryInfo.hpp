//
//  RepositoryInfo.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-31.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef __NyxTraceViewer__RepositoryInfo__
#define __NyxTraceViewer__RepositoryInfo__


#include "Nyx.hpp"

#include <list>


/**
 *
 */
class CRepositoryInfo : public Nyx::CRefCount_Impl<>
{
public:
    CRepositoryInfo(const Nyx::CAString& name);
    virtual ~CRepositoryInfo();
    
    const Nyx::CAString&    Name() const            { return m_Name; }
    
protected:
    
    Nyx::CAString       m_Name;
};


DECLARE_OBJECTREF(CRepositoryInfo);



typedef     std::list<CRepositoryInfoRef>      RepositoryInfoList;


#endif /* defined(__NyxTraceViewer__RepositoryInfo__) */
