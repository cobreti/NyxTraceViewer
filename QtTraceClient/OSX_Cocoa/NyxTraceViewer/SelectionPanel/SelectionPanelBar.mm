//
//  SelectionPanelBar.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-07.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "SelectionPanelBar.h"
#import "../Controls/ToggleFlatBtn.h"

#include <Nyx.hpp>

enum {
    kChannelsHidden = 0,
    kChannelsVisible = 1,
    kSourcesHidden = 2,
    kSourcesVisible = 3,

    kChannels = 0,
    kSources = 1,
    
    kTopMargin = 5,
    kBottomMargin = 5,
    kInterBtnSpace = 10
};



@implementation CSelectionPanelBar

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {

        m_SelectionBar = [[CSelectionBar alloc] initWithFrame: NSZeroRect];
        [m_SelectionBar setBtnSelectionChangedHandler: CActionHandlerInfo(@selector(onSelectionBarSelectedBtnChanged:), self)];
        [self addSubview: m_SelectionBar];
        
        CToggleFlatBtn* pChannelsBtn = [[CToggleFlatBtn alloc] initWithFrame: NSZeroRect];
        [pChannelsBtn setStateImg:kToggleFlatBtn_OffState withResourceImage:@"channels_hidden" withSize:NSMakeSize(16, 16)];
        [pChannelsBtn setStateImg:kToggleFlatBtn_OnState withResourceImage:@"channels_visible" withSize:NSMakeSize(16, 16)];
        [pChannelsBtn setId: kSelectionPanelBar_ChannelsPanel];

        CToggleFlatBtn* pSourcesBtn = [[CToggleFlatBtn alloc] initWithFrame: NSZeroRect];
        [pSourcesBtn setStateImg:kToggleFlatBtn_OffState withResourceImage:@"sources_hidden" withSize:NSMakeSize(16, 16)];
        [pSourcesBtn setStateImg:kToggleFlatBtn_OnState withResourceImage:@"sources_visible" withSize:NSMakeSize(16, 16)];
        [pSourcesBtn setId: kSelectionPanelBar_SourcesPanel];
                
        [pSourcesBtn setState: kToggleFlatBtn_OnState];
        [m_SelectionBar addBtn: pSourcesBtn];
        [m_SelectionBar addBtn: pChannelsBtn];
        [m_SelectionBar calcSize];
        m_SelectionBar.translatesAutoresizingMaskIntoConstraints = NO;
        
        [self addConstraint: [NSLayoutConstraint constraintWithItem:self
                                                         attribute: NSLayoutAttributeHeight
                                                         relatedBy: NSLayoutRelationEqual
                                                         toItem: m_SelectionBar
                                                         attribute: NSLayoutAttributeHeight
                                                         multiplier: 1
                                                         constant: 0 ]];

        [self addConstraint: [NSLayoutConstraint constraintWithItem:m_SelectionBar
                                                          attribute: NSLayoutAttributeTop
                                                          relatedBy: NSLayoutRelationEqual
                                                             toItem: self
                                                          attribute: NSLayoutAttributeTop
                                                         multiplier: 0
                                                           constant: 0 ]];
        
        [self addConstraint: [NSLayoutConstraint constraintWithItem:m_SelectionBar
                                                          attribute: NSLayoutAttributeCenterX
                                                          relatedBy: NSLayoutRelationEqual
                                                             toItem: self
                                                          attribute: NSLayoutAttributeCenterX
                                                         multiplier: 1
                                                           constant: 0 ]];

    }
    
    return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
    [super drawRect: dirtyRect];
        
    [[NSColor lightGrayColor] set];
    
    NSBezierPath*       path = [NSBezierPath alloc];
    
    [path appendBezierPathWithRect:[self frame]];
    [path fill];
}

- (IBAction) onSelectionBarSelectedBtnChanged: (id)sender
{
    if (m_PanelSelectionChangedHandler.Valid())
        [self sendAction: m_PanelSelectionChangedHandler.Selector() to:m_PanelSelectionChangedHandler.Target()];
}


- (void)calcSize
{
}

- (void)dealloc
{
    [m_SelectionBar release];
    
    [super dealloc];
}

- (BOOL)isFlipped
{
    return YES;
}

- (void)viewDidEndLiveResize
{
}

- (void)onSourcesSelected: (id)sender
{
    NYXTRACE(0x0, L"sources button clicked");
}


- (void)setPanelSelectionChangedHandler: (const CActionHandlerInfo&)handler
{
    m_PanelSelectionChangedHandler = handler;
}

- (int)selectedPanel
{
    CToggleFlatBtn* pBtn = [m_SelectionBar activeBtn];
    
    if (pBtn)
        return [pBtn getId];
    
    return 0;
}



@end

