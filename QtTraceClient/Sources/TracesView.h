#ifndef TRACESVIEW_H
#define TRACESVIEW_H

#include <QWidget>
#include <QToolBar>
#include <QPushButton>
#include <QTimer>
#include <QBrush>

#include "View/ViewSettings.hpp"
#include "View/TracesViewCore.hpp"
#include "View/Highlight/ViewItemHighlightersSet.hpp"
#include "TracesGroupNotificationsListener.h"
#include "View/ViewTracesIterator.hpp"
#include "View/ViewTracesContentIterator.hpp"
#include "View/ViewTracesDisplayCache.h"
#include "View/ViewSettings.hpp"
#include "View/Decorations/StaticHighlights.hpp"


namespace Ui
{
    class CTracesView;
}

class CViewHeader;
class QToolButton;
class CHighlightBrush;
class CHighlightColorsPopup;
class QFile;
class CTracesGroupView;


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

    const CViewSettings&		Settings() const		{ return m_Settings; }
    CViewSettings&				Settings()				{ return m_Settings; }

    CViewItemHighlightersSetRef Highlighters() const    { return m_refHighlighters; }

    CTracesViewCore*            ViewCore() const        { return m_refViewCore; }

    CTracesGroupView*           TracesGroupView() const     { return m_pCurrentTracesGroupView; }
//    CDynamicHighlightsDirectory&     dynamicHighlights()        { return m_DynamicHighlights; }

    CViewTracesContentIterator&     focusedItem()               { return m_FocusedItem; }
    CViewTracesIterator&            topPos()                    { return m_TopPos; }

    CViewTracesIterator             FirstPos() const;
    CViewTracesIterator             LastPos() const;

    void                            setKeepAtEnd(bool keepAtEnd);

    void MakeFocusedItemVisible();

    void OnNewTraces();

    void Save( const QString& filename );
    void Clear();

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


signals:

    void keepAtEndDisabled();


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
    virtual void MovePosToDisplayLastLine();

    virtual bool updatingScrollPos() const      { return m_bUpdatingScrollPos; }

protected:

    class XScrollPosUpdate
    {
    public:
        XScrollPosUpdate(CTracesView& rView) : m_rView(rView)
        {
            m_rView.m_bUpdatingScrollPos = true;
        }

        ~XScrollPosUpdate()
        {
            m_rView.m_bUpdatingScrollPos = false;
        }


    protected:
        CTracesView&        m_rView;
    };

protected:

    Ui::CTracesView*			        ui;
    QString								m_Name;
    QRectF								m_Margins;
    bool                                m_bViewDirty;
    CViewHeader*                        m_pHeader;
    QTimer                              m_RefreshTimer;
    CTracesViewCoreRef                  m_refViewCore;

    CViewItemHighlightersSetRef         m_refHighlighters;

    CHighlightBrush*                    m_pLastSelectedBrush;

    CHighlightColorsPopup*              m_pHighlightColorsPopup;

    CTracesGroupNotificationsListener   m_TracesGroupNotificationsListener;
    TraceClientCore::CTracesGroup*      m_pCurrentTracesGroup;
    CViewTracesIterator                 m_TopPos;
    CViewTracesContentIterator          m_FocusedItem;
    CViewTracesDisplayCache             m_DisplayCache;

    CStaticHighlights                   m_LiveStaticHighlights;

    CTracesGroupView*                   m_pCurrentTracesGroupView;

    bool                                m_bUpdatingScrollPos;

    QRect                               m_SelectionArea;
    QBrush                              m_SelectionBrush;
    QBrush                              m_SelectionBorderBrush;

    CViewSettings                       m_Settings;
};

#endif // TRACESVIEW_H
