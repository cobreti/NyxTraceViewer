#ifndef _TRACESVIEWCOLUMNSARRAY_HPP_
#define _TRACESVIEWCOLUMNSARRAY_HPP_

#include "TracesViewColumnSettings.hpp"

using namespace System::Collections;

/**
 *
 */
public ref class CTracesViewColumnsArray
{
public:
	CTracesViewColumnsArray();
	virtual ~CTracesViewColumnsArray();


	virtual void Add( CTracesViewColumnSettings^ pColumnSettings );


	virtual property CTracesViewColumnSettings^ Item[ETracesViewColumnID^]
	{
		CTracesViewColumnSettings^ get(ETracesViewColumnID^ key) { return (CTracesViewColumnSettings^)m_IndexedColumns[key]; }
	}


	virtual property CTracesViewColumnSettings^ Item[int]
	{
		CTracesViewColumnSettings^ get(int index)
		{
			ETracesViewColumnID^		ID = (ETracesViewColumnID^)m_Columns[index];
			return (CTracesViewColumnSettings^)m_IndexedColumns[ID];
		}

		void set(int index, CTracesViewColumnSettings^ pSettings)
		{
			m_Columns->Insert(index, pSettings->ID);
			//m_Columns[index] = pSettings->ID;
			m_IndexedColumns[pSettings->ID] = pSettings;
		}
	}

	virtual property int Count
	{
		int get() { return m_Columns->Count; }
	}

protected:

	ArrayList^		m_Columns;
	Hashtable^		m_IndexedColumns;
};


#endif // _TRACESVIEWCOLUMNSARRAY_HPP_
