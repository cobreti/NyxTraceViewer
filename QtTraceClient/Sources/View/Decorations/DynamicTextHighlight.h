#ifndef DYNAMICTEXTHIGHLIGHT_H
#define DYNAMICTEXTHIGHLIGHT_H

#include "DynamicHighlight.h"


class CDynamicTextHighlight : public CDynamicHighlight
{
public:
    CDynamicTextHighlight();
    virtual ~CDynamicTextHighlight();

    const QString&          text() const            { return m_Text; }
    QString&                text()                  { return m_Text; }

    const QColor&           color() const           { return m_Color; }
    QColor&                 color()                 { return m_Color; }

     virtual void Draw( CViewTracePainter::CPaintContext& context );

protected:

    QString         m_Text;
    QColor          m_Color;
};


#endif // DYNAMICTEXTHIGHLIGHT_H
