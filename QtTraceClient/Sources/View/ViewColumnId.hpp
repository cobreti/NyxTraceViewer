#ifndef _VIEWCOLUMNID_HPP_
#define _VIEWCOLUMNID_HPP_

#include <vector>


enum EViewColumnId
{
    eVCI_TickCount  = 0,
    eVCI_ThreadId   = 1,
    eVCI_Data       = 2,
    eVCI_ModuleName = 3,
    eVCI_LineNumber = 4,
    eVCI_Count      = 5
};


typedef std::vector<EViewColumnId>      ColumnsIdVector;


#endif // _VIEWCOLUMNID_HPP_
