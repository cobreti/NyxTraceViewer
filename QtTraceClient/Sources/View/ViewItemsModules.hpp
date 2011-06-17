#ifndef _VIEWITEMSMODULES_HPP_
#define _VIEWITEMSMODULES_HPP_


#include <Nyx.hpp>
#include <set>

class CModuleViewItems;


/**
 *
 */
typedef     std::set<CModuleViewItems*>      ModuleViewItemsSet;


/**
 *
 */
class CViewItemsModules : public ModuleViewItemsSet
{
public:
    CViewItemsModules();
    ~CViewItemsModules();
};

#endif // _VIEWITEMSMODULES_HPP_
