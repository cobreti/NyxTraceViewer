//
//  ContentView.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-20.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "ContentView.h"
#import "TracesDataView.h"


@implementation CContentView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {

    }
    
    return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
	[super drawRect:dirtyRect];
    
//    [[NSColor redColor] set];
//    
//    NSBezierPath*       path = [NSBezierPath alloc];
//    
//    NSRect  rc = [self frame];
//    rc.origin = NSZeroPoint;
//    
//    [path appendBezierPathWithOvalInRect: rc];
//    
//    [path stroke];
	
}

- (void)awakeFromNib
{
    [self initSettings];
    [self createTracesScrollView];
    [self createTracesDataView];
}


- (void) createTracesScrollView
{
    m_TracesScrollView = [[NSScrollView alloc] initWithFrame: NSZeroRect];
    [m_TracesScrollView setHasHorizontalScroller: YES];
    [m_TracesScrollView setHasVerticalScroller: YES];
    [self addSubview: m_TracesScrollView];
    
    m_TracesScrollView.translatesAutoresizingMaskIntoConstraints = NO;
    
    [self addConstraint: [NSLayoutConstraint constraintWithItem: m_TracesScrollView
                                                      attribute: NSLayoutAttributeTop
                                                      relatedBy: NSLayoutRelationEqual
                                                         toItem: self
                                                      attribute: NSLayoutAttributeTop
                                                     multiplier: 0
                                                       constant: 0 ]];
    
    [self addConstraint: [NSLayoutConstraint constraintWithItem: m_TracesScrollView
                                                      attribute: NSLayoutAttributeLeft
                                                      relatedBy: NSLayoutRelationEqual
                                                         toItem: self
                                                      attribute: NSLayoutAttributeLeft
                                                     multiplier: 0
                                                       constant: 0 ]];

    [self addConstraint: [NSLayoutConstraint constraintWithItem: m_TracesScrollView
                                                      attribute: NSLayoutAttributeWidth
                                                      relatedBy: NSLayoutRelationEqual
                                                         toItem: self
                                                      attribute: NSLayoutAttributeWidth
                                                     multiplier: 1
                                                       constant: 0 ]];

    [self addConstraint: [NSLayoutConstraint constraintWithItem: m_TracesScrollView
                                                      attribute: NSLayoutAttributeHeight
                                                      relatedBy: NSLayoutRelationEqual
                                                         toItem: self
                                                      attribute: NSLayoutAttributeHeight
                                                     multiplier: 1
                                                       constant: 0 ]];
}


- (void) createTracesDataView
{
    m_TracesDataView = [[CTracesDataView alloc] initWithFrame: NSMakeRect(0, 0, 400, 200)];
    [m_TracesDataView setSettings: &m_Settings];
    [m_TracesScrollView setDocumentView: m_TracesDataView];
}

- (void) initSettings
{
    
    m_Settings.setFont( [NSFont fontWithName: @"arial" size:12] );
    
    CTracesDataViewSettings::TColumnsOrder      colsOrder;
    
    colsOrder.push_back( CTracesDataViewSettings::eColumn_LineNumber );
    colsOrder.push_back( CTracesDataViewSettings::eColumn_Data );
    m_Settings.setColumnsOrder(colsOrder);
    
    m_Settings.setColumnSettings(CTracesDataViewSettings::eColumn_LineNumber, CColumnSettings());
    m_Settings.setColumnSettings(CTracesDataViewSettings::eColumn_Data, CColumnSettings());
}

- (void) onTracesGroupChanged: (TraceClientCore::CTracesGroup*)pTracesGroup
{
    [m_TracesDataView onTracesGroupChanged: pTracesGroup];
}

@end
