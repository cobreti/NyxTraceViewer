#ifndef VIEWITEMSETTINGS_HPP
#define VIEWITEMSETTINGS_HPP


#include <Nyx.hpp>
#include <QWidget>


DECLARE_OBJECTREF(CViewItemSettings);

/**
 *
 */
class CViewItemSettings : public Nyx::CRefCount_Impl<>
{
public:
    CViewItemSettings();
	CViewItemSettings(const CViewItemSettings& settings);
    virtual ~CViewItemSettings();

    QFont*  GetFont() const     { return m_pFont; }
    void SetFont( QFont* pFont );

    int FontHeight() const;

	const CViewItemSettings& operator = (const CViewItemSettings& settings);

	CViewItemSettings* Clone() const;

protected:

	void CopyFrom( const CViewItemSettings& settings );

protected:

    QFont*                  m_pFont;
    int                     m_FontHeight;
};

#endif // VIEWITEMSETTINGS_HPP
