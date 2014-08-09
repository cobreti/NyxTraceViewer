//
//  TracesGroupsListCtrl.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-08.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "TracesGroupsListCtrl.h"
#import "TracesGroupItem.h"
#import "../CellsLayout/VerticalCellsLayout.h"
#import "../CellsLayout/CellLayoutItem.h"
#import "TracesGroupLayoutRow.h"

#include "TracesGroupInfo.h"


@implementation CTracesGroupsListCtrl

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        
        m_Layout = [[CVerticalCellsLayout alloc] init];
        m_SelectedRow = nil;
        
//        [self addTracesGroup: new CTracesGroupInfo(Nyx::CAString("first group"))];
//        [self addTracesGroup: new CTracesGroupInfo(Nyx::CAString("second group"))];
//        [self addTracesGroup: new CTracesGroupInfo(Nyx::CAString("third group"))];
//        [self addTracesGroup: new CTracesGroupInfo(Nyx::CAString("fourth group"))];
    }
    
    return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
    [super drawRect: dirtyRect];
    
    NSRect      parentFrame = [[self superview] frame];
    NSRect      rc = [self frame];
    
    rc.size.width = MAX(rc.size.width, parentFrame.size.width);
    
    [m_Layout drawInView: self withRect: rc];
}

- (void)calcSize
{
    NSRect      parentFrame = [[self superview] frame];
    NSRect      frame;
    
    [m_Layout update: NSZeroPoint];
    
    frame = [m_Layout layoutRect];
    frame.size.width = MAX(frame.size.width, parentFrame.size.width);
    
    [self setFrame: frame];
}

- (NSSize)intrinsicContentSize
{
    return [self frame].size;
}


- (BOOL)isFlipped
{
    return YES;
}


- (void)addTracesGroup: (CTracesGroupInfo*) info
{
    NSString* name = [[NSString alloc] initWithCString: info->Name().c_str() encoding:NSMacOSRomanStringEncoding];
    NSCell* nameCell = [[NSCell alloc] initTextCell: name];
    
    CTracesGroupLayoutRow* layoutRow = [[CTracesGroupLayoutRow alloc] init];
    
    [layoutRow addItem: [[CCellLayoutItem alloc] initWithCell:nameCell] ];
    [layoutRow setMargins: MakeLayoutMargins(22, 5, 22, 5)];
    [layoutRow setTracesGroupInfo: info];
    [m_Layout addItem: layoutRow];
    [self calcSize];
    [self setNeedsDisplay: YES];
}


- (void)mouseDown:(NSEvent *)theEvent
{
    NSMutableArray*     pickResult = [[NSMutableArray alloc] initWithCapacity:10];
    
    [m_Layout pick:pickResult atPoint: [self convertPoint:[theEvent locationInWindow] fromView: nil] ];
    
    NSInteger   pickCount = [pickResult count];
    
    if ( pickCount > 2 )
    {
        if ( m_SelectedRow != nil )
        {
            [m_SelectedRow setSelected:NO];
            m_SelectedRow = nil;
        }

        m_SelectedRow = [pickResult objectAtIndex:pickCount-2];
        [m_SelectedRow setSelected: YES];
        
        CTracesGroupInfo*   info = [m_SelectedRow tracesGroupInfo];
        NSString* name = [[NSString alloc] initWithCString: info->Name().c_str() encoding:NSMacOSRomanStringEncoding];
        [[self window] setTitle: name];
        
        [self sendAction: m_SelChangeHandler.Selector() to: m_SelChangeHandler.Target()];
    }
    
    [pickResult release];
    
    [self setNeedsDisplay: YES];
}

- (CTracesGroupInfo*)selection
{
    if ( NULL == m_SelectedRow )
        return NULL;
    
    return [m_SelectedRow tracesGroupInfo];
}

- (void)setFrame: (NSRect)framesize
{
    NSRect frame = [m_Layout layoutRect];
    
    framesize.size.height = MAX(framesize.size.height, frame.size.height);
    
    [super setFrame: framesize];
}


- (void)setSelChangeHandler:(const CActionHandlerInfo&)handler
{
    m_SelChangeHandler = handler;
}

@end

