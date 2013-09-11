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
        
        [self addTracesGroup: new CTracesGroupInfo(Nyx::CAString("first group"))];
        [self addTracesGroup: new CTracesGroupInfo(Nyx::CAString("second group"))];
        [self addTracesGroup: new CTracesGroupInfo(Nyx::CAString("third group"))];
        [self addTracesGroup: new CTracesGroupInfo(Nyx::CAString("fourth group"))];
    }
    
    return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
    [super drawRect: dirtyRect];
    
    [m_Layout drawInView: self];
}

- (void)calcSize
{
    [m_Layout update: NSZeroPoint];
    [self setFrame: [m_Layout layoutRect]];
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
    [m_Layout addItem: layoutRow];
}


@end

