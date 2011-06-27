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

signals:

public slots:

protected:

    virtual void paintEvent(QPaintEvent* event);
    virtual void SetBkgndColor( const QColor& color );

protected:

    CViewColumnsSettings&       m_rColumnsSettings;
    int                         m_HorzOffset;
    QFont*                      m_pFont;
    QRect                       m_Margins;
    QImage*                     m_pBkgndImage;
};

#endif // VIEWHEADER_HPP
