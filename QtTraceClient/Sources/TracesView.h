#ifndef TRACESVIEW_H
#define TRACESVIEW_H

#include <QWidget>
#include <QToolBar>
#include <QPushButton>
#include <QTimer>
#include "View/ViewSettings.hpp"
#include "View/TracesViewCore.hpp"
#include "View/Highlight/ViewItemHighlightersSet.hpp"
#include "TracesGroupNotificationsListener.h"
#include "View/ViewTracesIterator.hpp"
#include "View/ViewTracesDisplayCache.h"
#include "View/Decorations/ViewTraceObjectsDirectory.h"

namespace Ui
{
    class CTracesView;
}

class CViewHeader;
class QToolButton;
class CHighlightBrush;
class CHighlightColorsPopup;
class QFile;


/**
 *
 */
class CTracesView : public QWidget
{
    Q_OBJECT

public:
    explicit CTracesView(QWidget* pParent, CTracesView* pBase);
    ~CTracesView();

	void SetName( const QString& name );
	const QString& Name() const		{ return m_Name; }

    const CViewSettings&		Settings() const		{ return ViewCore()->ViewSettings(); }
    CViewSettings&				Settings()				{ return ViewCore()->ViewSettings(); }

    CViewItemHighlightersSetRef Highlighters() const    { return m_refHighlighters; }

    CTracesViewCore*            ViewCore() const        { return m_refViewCore; }

    void OnNewTraces();

    void Save( const QString& filename );

    const QRectF                ViewRect() const;
    int                         NumberOfLinesVisibles() const;

    void Invalidate(bool dirty);

    void SetTracesGroup( TraceClientCore::CTracesGroup* pGroup );

public slots:

    void OnVertSliderPosChanged(int value);
    void OnHorzSliderPosChanged(int value);
    void RefreshDisplay();
    void OnChooseHighlightBrush( CHighlightBrush* pBrush );
    void OnViewBeginUpdate( TraceClientCore::CTracesGroup* pGroup, TraceClientCore::CTracesView* pView );
    void OnViewEndUpdate( TraceClientCore::CTracesGroup* pGroup, TraceClientCore::CTracesView* pView );

protected:

    virtual void resizeEvent(QResizeEvent* event);
    virtual void paintEvent(QPaintEvent* event);
	virtual void closeEvent(QCloseEvent* event);
    virtual void UpdateScrollbarRange(const QRect& rcClient);
	virtual void keyPressEvent( QKeyEvent* event );
	virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* event);
    virtual void showEvent( QShowEvent* event);

    void Init(CTracesView* pBase);

    virtual QRect ClientRect() const { return ClientRect(rect()); }
    virtual QRect ClientRect( const QRect& rcWnd ) const;
    virtual QSize HeaderSize() const;

protected:

    Ui::CTracesView*			        ui;
    QString								m_Name;
    QRectF								m_Margins;
    bool                                m_bViewDirty;
    bool                                m_bKeepAtEnd;
    CViewHeader*                        m_pHeader;
    QTimer                              m_RefreshTimer;
    CTracesViewCoreRef                  m_refViewCore;

    CViewItemHighlightersSetRef         m_refHighlighters;

    CHighlightBrush*                    m_pLastSelectedBrush;

    CHighlightColorsPopup*              m_pHighlightColorsPopup;

    CTracesGroupNotificationsListener   m_TracesGroupNotificationsListener;
    TraceClientCore::CTracesGroup*      m_pCurrentTracesGroup;
    CViewTracesIterator                 m_TopPos;
    CViewTracesDisplayCache             m_DisplayCache;

    CViewTraceObjectsDirectory          m_TraceSectionsHilights;

    QRect                               m_SelectionArea;
};

#endif // TRACESVIEW_H
