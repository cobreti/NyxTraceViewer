#ifndef _COLORBTN_H_
#define _COLORBTN_H_

#include <QToolButton>


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

public slots:

    void OnChooseColor();

protected:

    virtual void paintEvent(QPaintEvent*);

protected:

    QColor      m_Color;
};


#endif // _COLORBTN_H_
