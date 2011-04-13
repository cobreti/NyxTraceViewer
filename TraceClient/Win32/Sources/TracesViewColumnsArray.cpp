#include "TracesViewColumnsArray.hpp"


/**
 *
 */
CTracesViewColumnsArray::CTracesViewColumnsArray()
{
	m_Columns = gcnew ArrayList();
	m_IndexedColumns = gcnew Hashtable();
}


/**
 *
 */
CTracesViewColumnsArray::~CTracesViewColumnsArray()
{
	delete m_Columns;
}


/**
 *
 */
void CTracesViewColumnsArray::Add( CTracesViewColumnSettings^ pColumnSettings )
{
	m_Columns->Add(pColumnSettings->ID);

	m_IndexedColumns[pColumnSettings->ID] = pColumnSettings;
}
