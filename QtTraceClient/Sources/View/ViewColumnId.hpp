#ifndef _VIEWCOLUMNID_HPP_
#define _VIEWCOLUMNID_HPP_

#include <vector>


enum EViewColumnId
{
	eVCI_TickCount = 0,
	eVCI_ThreadId,
	eVCI_Data,
	eVCI_ModuleName,
    eVCI_LineNumber,
	eVCI_Count
};


typedef std::vector<EViewColumnId>      ColumnsIdVector;


#endif // _VIEWCOLUMNID_HPP_
