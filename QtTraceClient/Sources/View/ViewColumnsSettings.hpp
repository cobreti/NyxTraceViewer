#ifndef _VIEWCOLUMNSSETTINGS_HPP_
#define _VIEWCOLUMNSSETTINGS_HPP_

#include "ViewColumnsOrder.hpp"

#include <QtGlobal>
#include <map>


class CViewColumnSettings;


/**
 *
 */
class CViewColumnsSettings
{
public:
	CViewColumnsSettings();
	virtual ~CViewColumnsSettings();

	const CViewColumnsOrder&		Order() const		{ return m_ColumnsOrder; }
	CViewColumnsOrder&				Order()				{ return m_ColumnsOrder; }

	void Set( EViewColumnId ColumnId, CViewColumnSettings* pSettings );

    const CViewColumnSettings& operator [] ( EViewColumnId id ) const;
    CViewColumnSettings& operator [] ( EViewColumnId id );

    qreal GetTotalWidth() const;

    void UpdateFrom( const CViewColumnsSettings& settings );

    const CViewColumnsSettings& operator = (const CViewColumnsSettings& settings);

protected:

	typedef		std::map<EViewColumnId, CViewColumnSettings*>		ColumnSettingsTable;

protected:

    void ClearSettings();

protected:

	CViewColumnsOrder		m_ColumnsOrder;
	size_t					m_VisibleColumnsCount;
	ColumnSettingsTable		m_Settings;
};


#endif // _VIEWCOLUMNSSETTINGS_HPP_

