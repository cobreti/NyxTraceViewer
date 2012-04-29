#ifndef TRACESVIEW_H
#define TRACESVIEW_H

//#include <QtGUI>

#include <QWidget>
#include <QToolBar>
#include <QPushButton>
#include <QTimer>
#include "View/ViewItems.hpp"
#include "View/ViewSettings.hpp"
#include "View/IViewItemsModulesListener.hpp"
#include "View/TracesViewCore.hpp"


namespace Ui
{
    class CTracesView;
}

class CViewHeader;
class QToolButton;
class CModuleViewItems;
class CSessionViewItems;
class CViewItemsWalker;
class QFile;


/**
 *
 */
class CTracesView : public QWidget,
                    public IViewItemsModulesListener
{
    Q_OBJECT

public:
    explicit CTracesView(QWidget *parent = NULL);
    ~CTracesView();

    void InitFromView( const CTracesView& view );

	void SetName( const QString& name );
	const QString& Name() const		{ return m_Name; }

	const CViewSettings&		Settings() const		{ return m_Settings; }
	CViewSettings&				Settings()				{ return m_Settings; }

    CTracesViewCore*            ViewCore() const        { return m_refViewCore; }

    void OnNewTraces();

    void UpdateVisibleLines( const CViewSettings& settings );

    virtual void OnNewModuleViewItems( CModuleViewItems* pModule );
    virtual void OnNewSessionViewItems( CModuleViewItems* pModule, CSessionViewItems* pSession );

    void Save( const QString& filename );

public slots:

    void OnVertSliderPosChanged(int value);
    void OnHorzSliderPosChanged(int value);
    void RefreshDisplay();

protected:

    virtual void resizeEvent(QResizeEvent* event);
    virtual void paintEvent(QPaintEvent* event);
	virtual void closeEvent(QCloseEvent* event);
    virtual void UpdateScrollbarRange(const QRect& rcClient);
	virtual void keyPressEvent( QKeyEvent* event );
	virtual void mousePressEvent( QMouseEvent* event );
    virtual void wheelEvent(QWheelEvent* event);
    virtual void showEvent( QShowEvent* event);

	virtual void InitSettings();

    virtual QRect ClientRect() const { return ClientRect(rect()); }
    virtual QRect ClientRect( const QRect& rcWnd ) const;
    virtual QSize HeaderSize() const;

    virtual bool UpdateVisibleLines();

protected:

    enum
    {
        kPanel_LeftMargin = 50,
        kPanel_RightMargin = 50
    };

    Ui::CTracesView*			        ui;
    QString								m_Name;
    QRectF								m_Margins;
    CViewSettings						m_Settings;
    bool                                m_bViewDirty;
    bool                                m_bKeepAtEnd;
    CViewHeader*                        m_pHeader;
    CViewItemsWalker*                   m_pItemsWalker;
    QTimer                              m_RefreshTimer;
    CTracesViewCoreRef                  m_refViewCore;
};

#endif // TRACESVIEW_H
