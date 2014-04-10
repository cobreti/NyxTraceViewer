#ifndef _VIEWCOLUMNSETTINGS_HPP_
#define _VIEWCOLUMNSETTINGS_HPP_

#include <QtGlobal>
#include <QString>
#include "ViewItemMargins.hpp"

/**
 *
 */
class CViewColumnSettings
{
public:
	CViewColumnSettings();
    CViewColumnSettings(const CViewColumnSettings& settings);
	virtual ~CViewColumnSettings();

	const qreal& GetWidth() const		{ return m_Width; }
	void SetWidth( const qreal& width );

	bool GetVisible() const				{ return m_bVisible; }
	void SetVisible(bool bVisible)		{ m_bVisible = bVisible; }

	const QString& GetTitle() const		{ return m_Title; }
	void SetTitle(const QString& title)	{ m_Title = title; }

    const CViewItemMargins&     Margins() const     { return m_Margins; }
    CViewItemMargins&           Margins()           { return m_Margins; }

    bool        AutoWidth() const       { return m_bAutoWidth; }
    bool&       AutoWidth()             { return m_bAutoWidth; }

protected:

	qreal								m_Width;
	bool								m_bVisible;
	QString								m_Title;
    CViewItemMargins                    m_Margins;
    bool                                m_bAutoWidth;
};

#endif // _VIEWCOLUMNSETTINGS_HPP_
