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
        // Initialization code here.
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
                                                       constant: 10 ]];
    
    [self addConstraint: [NSLayoutConstraint constraintWithItem: m_TracesScrollView
                                                      attribute: NSLayoutAttributeLeft
                                                      relatedBy: NSLayoutRelationEqual
                                                         toItem: self
                                                      attribute: NSLayoutAttributeLeft
                                                     multiplier: 0
                                                       constant: 10 ]];

    [self addConstraint: [NSLayoutConstraint constraintWithItem: m_TracesScrollView
                                                      attribute: NSLayoutAttributeWidth
                                                      relatedBy: NSLayoutRelationEqual
                                                         toItem: self
                                                      attribute: NSLayoutAttributeWidth
                                                     multiplier: 1
                                                       constant: -20 ]];

    [self addConstraint: [NSLayoutConstraint constraintWithItem: m_TracesScrollView
                                                      attribute: NSLayoutAttributeHeight
                                                      relatedBy: NSLayoutRelationEqual
                                                         toItem: self
                                                      attribute: NSLayoutAttributeHeight
                                                     multiplier: 1
                                                       constant: -20 ]];
}


- (void) createTracesDataView
{
    m_TracesDataView = [[CTracesDataView alloc] initWithFrame: NSMakeRect(0, 0, 200, 200)];
    [m_TracesScrollView setDocumentView: m_TracesDataView];
}


- (void) onTracesGroupChanged: (TraceClientCore::CTracesGroup*)pTracesGroup
{
    [m_TracesDataView onTracesGroupChanged: pTracesGroup];
}

@end
