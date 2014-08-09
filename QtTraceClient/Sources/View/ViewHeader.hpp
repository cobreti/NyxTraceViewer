#ifndef VIEWHEADER_HPP
#define VIEWHEADER_HPP

#include <QWidget>
#include <QResizeEvent>


class CViewColumnsSettings;


/**
 *
 */
class CViewHeader : public QWidget
{
    Q_OBJECT
public:
    explicit CViewHeader(CViewColumnsSettings& rColumnsSettings, QWidget *parent = 0);
    virtual ~CViewHeader();

    void SetHorzOffset(int offset)      { m_HorzOffset = offset; }

    void InitDefaultWidth();
    void AdjustColumnsSize();

    const QRectF&       Margins() const     { return m_Margins; }
    QRectF&             Margins()           { return m_Margins; }

signals:

public slots:

protected:

    virtual void paintEvent(QPaintEvent* event);
    virtual void SetBkgndColor( const QColor& color );

protected:

    CViewColumnsSettings&       m_rColumnsSettings;
    int                         m_HorzOffset;
    QFont*                      m_pFont;
    QImage*                     m_pBkgndImage;
    QRectF                      m_Margins;
};

#endif // VIEWHEADER_HPP
