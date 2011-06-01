#ifndef TRACESVIEW_H
#define TRACESVIEW_H

#include <QWidget>
#include <QToolBar>
#include "View/ViewItems.hpp"
#include "View/ViewSettings.hpp"


namespace Ui
{
    class CTracesView;
}

class CTracesDocument;
class CViewHeader;

class CTracesView : public QWidget
{
    Q_OBJECT

public:
    explicit CTracesView(CTracesDocument& rDoc, QWidget *parent = NULL);
    ~CTracesView();

	void SetName( const QString& name );
	const QString& Name() const		{ return m_Name; }

	const CViewSettings&		Settings() const		{ return m_Settings; }
	CViewSettings&				Settings()				{ return m_Settings; }

    const CTracesDocument& Doc() const                  { return m_rDoc; }
    CTracesDocument& Doc()                              { return m_rDoc; }

    void OnNewTraces();

    void UpdateVisibleLines( const CViewSettings& settings );
    void RefreshDisplay();

public slots:

    void OnVertSliderPosChanged(int value);
    void OnHorzSliderPosChanged(int value);

protected:

    virtual void resizeEvent(QResizeEvent* event);
    virtual void paintEvent(QPaintEvent* event);
	virtual void closeEvent(QCloseEvent* event);
    virtual void UpdateScrollbarRange(const QRect& rcClient);
	virtual void keyPressEvent( QKeyEvent* event );
	virtual void mousePressEvent( QMouseEvent* event );
    virtual void wheelEvent(QWheelEvent* event);

	virtual void InitSettings();

    virtual QRect ClientRect() const { return ClientRect(rect()); }
    virtual QRect ClientRect( const QRect& rcWnd ) const;
    virtual QSize HeaderSize() const;

    virtual bool UpdateVisibleLines();

protected:

  Ui::CTracesView*											  ui;
  CTracesDocument&                        m_rDoc;
  QString														      m_Name;
  QRectF														      m_Margins;
  CViewItemPos                            m_TopPos;
  CViewSettings												    m_Settings;
  QSizeF                                  m_MaxLineSize;
  bool                                    m_bViewDirty;
  bool                                    m_bKeepAtEnd;
  CViewHeader*                            m_pHeader;
  QToolBar*                               m_pToolbar;
};

#endif // TRACESVIEW_H
