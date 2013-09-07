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

        NSString* channelsHiddenPath = [[NSBundle mainBundle] pathForResource:@"channels_hidden" ofType:@"png"];
        NSImage* channelsHiddenImg = [[NSImage alloc] initWithContentsOfFile:channelsHiddenPath];
        [channelsHiddenImg setSize: NSMakeSize(16, 16)];

        NSString* channelsVisiblePath = [[NSBundle mainBundle] pathForResource:@"channels_visible" ofType:@"png"];
        NSImage* channelsVisibleImg = [[NSImage alloc] initWithContentsOfFile:channelsVisiblePath];
        [channelsVisibleImg setSize: NSMakeSize(16, 16)];

        NSString* sourcesHiddenPath = [[NSBundle mainBundle] pathForResource:@"sources_hidden" ofType:@"png"];
        NSImage* sourcesHiddenImg = [[NSImage alloc] initWithContentsOfFile:sourcesHiddenPath];
        [sourcesHiddenImg setSize: NSMakeSize(16, 16)];
        
        NSString* sourcesVisiblePath = [[NSBundle mainBundle] pathForResource:@"sources_visible" ofType:@"png"];
        NSImage* sourcesVisibleImg = [[NSImage alloc] initWithContentsOfFile:sourcesVisiblePath];
        [sourcesVisibleImg setSize: NSMakeSize(16, 16)];

        m_Cells[kChannelsHidden] = [[NSCell alloc] initImageCell: channelsHiddenImg];
        m_Cells[kChannelsVisible] = [[NSCell alloc] initImageCell: channelsVisibleImg];
        m_Cells[kSourcesHidden] = [[NSCell alloc] initImageCell: sourcesHiddenImg];
        m_Cells[kSourcesVisible] = [[NSCell alloc] initImageCell: sourcesVisibleImg];
        
        CToggleFlatBtn* pChannelsBtn = [[CToggleFlatBtn alloc] initWithFrame: NSZeroRect];
        [pChannelsBtn setStateImg:kToggleFlatBtn_OffState withResourceImage:@"channels_hidden" withSize:NSMakeSize(16, 16)];
        [pChannelsBtn setStateImg:kToggleFlatBtn_OnState withResourceImage:@"channels_visible" withSize:NSMakeSize(16, 16)];
        m_Btns[kChannels] = pChannelsBtn;
//        [self addSubview: pChannelsBtn];

        CToggleFlatBtn* pSourcesBtn = [[CToggleFlatBtn alloc] initWithFrame: NSZeroRect];
        [pSourcesBtn setStateImg:kToggleFlatBtn_OffState withResourceImage:@"sources_hidden" withSize:NSMakeSize(16, 16)];
        [pSourcesBtn setStateImg:kToggleFlatBtn_OnState withResourceImage:@"sources_visible" withSize:NSMakeSize(16, 16)];
        m_Btns[kSources] = pSourcesBtn;
        [self addSubview: pSourcesBtn];
        
        SEL sel = NSSelectorFromString(@"onSourcesSelected:");
        [pSourcesBtn setAction: sel];
        [pSourcesBtn setTarget: self];
        
        pSourcesBtn.translatesAutoresizingMaskIntoConstraints = NO;
        
//        [pSourcesBtn addConstraints:[NSLayoutConstraint
//                              constraintsWithVisualFormat:@"V:|[pSourcesBtn(==16)]"
//                              options:0 metrics:nil views:NSDictionaryOfVariableBindings(pSourcesBtn)]];
        
//        [pSourcesBtn addConstraints:[NSLayoutConstraint
//                                     constraintsWithVisualFormat:@"|[pSourcesBtn(==16)]"
//                                     options:0 metrics:nil views:NSDictionaryOfVariableBindings(pSourcesBtn)]];

        [self addConstraint: [NSLayoutConstraint constraintWithItem:self
                                                         attribute: NSLayoutAttributeHeight
                                                         relatedBy: NSLayoutRelationEqual
                                                         toItem: pSourcesBtn
                                                         attribute: NSLayoutAttributeHeight
                                                         multiplier: 1
                                                         constant: 10 ]];

        [self addConstraint: [NSLayoutConstraint constraintWithItem:pSourcesBtn
                                                          attribute: NSLayoutAttributeTop
                                                          relatedBy: NSLayoutRelationEqual
                                                             toItem: self
                                                          attribute: NSLayoutAttributeTop
                                                         multiplier: 0
                                                           constant: 5 ]];
        
        [self addConstraint: [NSLayoutConstraint constraintWithItem:pSourcesBtn
                                                          attribute: NSLayoutAttributeCenterX
                                                          relatedBy: NSLayoutRelationEqual
                                                             toItem: self
                                                          attribute: NSLayoutAttributeCenterX
                                                         multiplier: 1
                                                           constant: 0 ]];

        //        [self addConstraint: [NSLayoutConstraint constraintWithItem:pSourcesBtn
//                                                          attribute: NSLayoutAttributeLeft
//                                                          relatedBy: NSLayoutRelationGreaterThanOrEqual
//                                                             toItem: self
//                                                          attribute: NSLayoutAttributeLeft
//                                                         multiplier: 1
//                                                           constant: 0 ]];

//        [self addConstraint: [NSLayoutConstraint constraintWithItem:pSourcesBtn
//                                                          attribute: NSLayoutAttributeCenterX
//                                                          relatedBy: NSLayoutRelationEqual
//                                                             toItem: self
//                                                          attribute: NSLayoutAttributeCenterX
//                                                         multiplier: 1
//                                                           constant: 0 ]];

        //        NSLayoutConstraint* constraint = [NSLayoutConstraint
//                                          constraintWithItem: pSourcesBtn
//                                          attribute:NSLayoutAttributeCenterX
//                                          relatedBy:NSLayoutRelationEqual
//                                          toItem: self
//                                          attribute: NSLayoutAttributeCenterX
//                                          multiplier: 1.0
//                                          constant: 5 ];
//        [self addConstraint: constraint];
    }
    
    return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
    [super drawRect: dirtyRect];
    
    NSRect  frame = [self frame];
    
    [[NSColor lightGrayColor] set];
    
    NSBezierPath*       path = [NSBezierPath alloc];
    
    [path appendBezierPathWithRect:[self frame]];
    [path fill];
}

- (void)calcSize
{
    NSRect  parentFrame = [[self superview] frame];
    NSSize  btnSize;
    NSSize  rowSize = NSZeroSize;
    NSPoint pt = NSZeroPoint;
    
    TToggleFlatBtnsMap::const_iterator      pos = m_Btns.begin();
        
    while (pos != m_Btns.end())
    {
        CToggleFlatBtn* pBtn = pos->second;
        
        [pBtn calcSize];
        btnSize = [pBtn frame].size;
        
        rowSize.height = MAX(rowSize.height, btnSize.height);
        rowSize.width += btnSize.width + kInterBtnSpace;
        
        ++ pos;
    }
    
    
//    pos = m_Btns.begin();
//    pt.y = kTopMargin;
//    pt.x = parentFrame.size.width/2 - rowSize.width/2;
//    
//    while (pos != m_Btns.end())
//    {
//        CToggleFlatBtn* pBtn = pos->second;
//        
//        [pBtn setFrameOrigin:pt];
//        pt.x += [pBtn frame].size.width + kInterBtnSpace;
//        
//        ++ pos;
//    }
    
    
//    [self setFrame: NSMakeRect(0, 0, parentFrame.size.width, rowSize.height + kTopMargin + kBottomMargin)];
}

- (void)dealloc
{
    TCellsMap::const_iterator       pos = m_Cells.begin();
    
    while (pos != m_Cells.end())
    {
        [pos->second release];
        ++ pos;
    }
    
    [super dealloc];
}

- (BOOL)isFlipped
{
    return YES;
}

- (void)viewDidEndLiveResize
{
//    [self calcSize];
}

- (void)onSourcesSelected: (id)sender
{
    NYXTRACE(0x0, L"sources button clicked");
}

@end

