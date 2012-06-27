#ifndef _COLORBTN_H_
#define _COLORBTN_H_

#include <QToolButton>

class CHighlightColorsPopup;
class CHighlightBrush;

/**
 *
 */
class CColorBtn : public QToolButton
{
    Q_OBJECT

public:
    CColorBtn();
    virtual ~CColorBtn();

    const QColor& Color() const         { return m_Color; }
    QColor& Color()                     { return m_Color; }

signals:

    void OnColorChanged(CColorBtn* pBtn);
    void OnColorSelected(CColorBtn* pBtn);

public slots:

    virtual void OnClicked();

protected:

    virtual void paintEvent(QPaintEvent*);

protected:

    QColor      m_Color;
};


/**
 *
 */
class CChooseColorBtn : public CColorBtn
{
    Q_OBJECT

public:
    CChooseColorBtn();
    virtual ~CChooseColorBtn();

public slots:

    virtual void OnClicked();
};


/**
 *
 */
class CWordHighlightColorBtn : public CColorBtn
{
    Q_OBJECT

public:
    CWordHighlightColorBtn();
    virtual ~CWordHighlightColorBtn();

    CHighlightBrush*        Brush() const       { return m_pBrush; }

signals:

    void OnWordHighlightChanged( CWordHighlightColorBtn* pBtn );

public slots:

    virtual void OnClicked();
    void OnChooseBrush(CHighlightBrush* pBrush);

protected:

    CHighlightColorsPopup*      m_pPopup;
    CHighlightBrush*            m_pBrush;
};


/**
 *
 */
class CHighlightBrushBtn : public CColorBtn
{
    Q_OBJECT

public:
    CHighlightBrushBtn();
    virtual ~CHighlightBrushBtn();

    CHighlightBrush*        Brush() const       { return m_pBrush; }
    void SetBrush( CHighlightBrush* pBrush );

signals:

    void OnBrushSelected( CHighlightBrushBtn* pBtn );

public slots:

    virtual void OnClicked();

protected:

    CHighlightBrush*        m_pBrush;
};


#endif // _COLORBTN_H_
