#include "ViewHeader.hpp"
#include "View/ViewColumnsSettings.hpp"
#include "View/ViewColumnSettings.hpp"

#include <QPainter>

/**
 *
 */
CViewHeader::CViewHeader(CViewColumnsSettings& rColumnsSettings, QWidget *parent) :
    QWidget(parent),
    m_rColumnsSettings(rColumnsSettings),
    m_HorzOffset(0),
    m_Margins(10, 10, 10, 20),
    m_pBkgndImage(NULL)
{
    resize(0, m_Margins.height());

    m_pFont = new QFont("Courier New", 11);
    m_pFont->setBold(true);
    m_pFont->setUnderline(true);

    //m_pBkgndImage = new QImage(":/View/Images/VGradientInner.png");
    SetBkgndColor( QColor(173, 229, 255) );
}


/**
 *
 */
CViewHeader::~CViewHeader()
{
    if ( m_pBkgndImage )
        delete m_pBkgndImage;
}


/**
 *
 */
void CViewHeader::InitDefaultWidth()
{
    size_t              ColsCount = m_rColumnsSettings.Order().Count();
    QFontMetrics        metrics(*m_pFont);
    int                 height = 0;
    int                 lWidth = 0;

    for (size_t index = 0; index < ColsCount; ++index)
    {
        EViewColumnId             id  = m_rColumnsSettings.Order()[index];
        CViewColumnSettings&      rSettings = m_rColumnsSettings[id];

        QRectF      rcText = metrics.boundingRect(rSettings.GetTitle());

        lWidth = rcText.width() + m_Margins.width();

        if ( lWidth > rSettings.GetWidth() )
            rSettings.SetWidth( lWidth );

        if ( rcText.height() > height )
            height = rcText.height();
    }

    resize( width(), height + m_Margins.height() );
}


void CViewHeader::AdjustColumnsSize()
{
    size_t              ColsCount = m_rColumnsSettings.Order().Count();
    QFontMetrics        metrics(*m_pFont);
    int                 height = 0;
    int                 lWidth = 0;

    for (size_t index = 0; index < ColsCount; ++index)
    {
        EViewColumnId             id  = m_rColumnsSettings.Order()[index];
        CViewColumnSettings&      rSettings = m_rColumnsSettings[id];

        QRectF      rcText = metrics.boundingRect(rSettings.GetTitle());

        lWidth = rcText.width() + m_Margins.width();

        if ( lWidth > rSettings.GetWidth() )
            rSettings.SetWidth( lWidth );

        if ( rcText.height() > height )
            height = rcText.height();
    }

    resize( width(), height + m_Margins.height() );
}


/**
 *
 */
void CViewHeader::paintEvent(QPaintEvent* pEvent)
{
    QPainter        painter(this);

    size_t      ColsCount = m_rColumnsSettings.Order().Count();
    int         headerHeight = size().height();
    qreal       x = m_Margins.left() - m_HorzOffset;
    int         ClientWidth = size().width();

    painter.setFont(*m_pFont);

    if ( m_pBkgndImage )
        painter.drawImage( QRect(0, 0, size().width(), size().height()),
                           *m_pBkgndImage );
    else
    {
        QBrush  bkgndBrush = palette().base();
        painter.fillRect(pEvent->rect(), bkgndBrush);
    }

    painter.setClipRect(m_Margins.left(), 0.0, rect().width(), rect().height());

    for (size_t index = 0; index < ColsCount && x < ClientWidth; ++index)
    {
        EViewColumnId                   id  = m_rColumnsSettings.Order()[index];
        const CViewColumnSettings&      rSettings = m_rColumnsSettings[id];

        painter.drawText( QRectF(   x + rSettings.Margins().left(),
                                    m_Margins.top(),
                                    rSettings.GetWidth(),
                                    headerHeight ),
                          Qt::AlignLeft, rSettings.GetTitle() );

        qreal colWidth = rSettings.GetWidth() + rSettings.Margins().width();
        x += colWidth;
    }
}


/**
 *
 */
void CViewHeader::SetBkgndColor( const QColor& color )
{
    if ( !m_pBkgndImage )
        return;

    int     ImageHeight = m_pBkgndImage->size().height();
    int     ImageWidth = m_pBkgndImage->size().width();
    int     x, y;

    for (y = 0; y < ImageHeight; ++y)
    {
        QColor      pixelColor = m_pBkgndImage->pixel(0, y);
        float       ratio = pixelColor.red() / 255.0;
        QColor      finalColor( color.red()*ratio, color.green()*ratio, color.blue()*ratio );

        for (x = 0; x < ImageWidth; ++x)
            m_pBkgndImage->setPixel(x, y, finalColor.rgb());
    }
}
