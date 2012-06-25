#ifndef _COLORBTN_H_
#define _COLORBTN_H_

#include <QToolButton>

class CHighlightColorsPopup;

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

public slots:

    virtual void OnClicked();
    void OnChooseColor(const QColor& color);

protected:

    CHighlightColorsPopup*      m_pPopup;
};

#endif // _COLORBTN_H_
