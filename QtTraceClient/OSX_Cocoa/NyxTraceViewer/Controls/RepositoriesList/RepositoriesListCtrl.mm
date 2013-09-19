//
//  RepositoriesListCtrl.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-31.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "RepositoriesListCtrl.h"
#import "../CellsLayout/VerticalCellsLayout.h"
#import "../CellsLayout/HorizontalCellsLayout.h"
#import "../CellsLayout/CellLayoutItem.h"
#import "RepositoriesListLayoutRow.h"

#include "TraceClientCoreModule.hpp"
#include "../TracesGroupsList/TracesGroupInfo.h"


@implementation CRepositoriesListCtrl

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
                
        m_Layout = [[CVerticalCellsLayout alloc] init];
        
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("first repository") )];
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("second repository") )];
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("third repository") )];
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("4 repository") )];
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("5 repository") )];
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("6 repository") )];
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("7 repository") )];
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("8 repository") )];
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("9 repository") )];
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("10 repository") )];
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("11 repository") )];
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("12 repository") )];
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("13 repository") )];
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("14 repository") )];
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("15 repository") )];
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("16 repository") )];
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("17 repository") )];
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("18 repository") )];
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("19 repository") )];
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("20 repository") )];
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("21 repository") )];
//        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("22 repository") )];       
    }
    
    return self;
}

- (BOOL)isFlipped
{
    return YES;
}


- (void)calcSize
{
    NSRect  parentFrame = [[self superview] frame];
    NSRect  frame;
    
    [m_Layout update:NSZeroPoint];
    
    frame = [m_Layout layoutRect];
    frame.size.width = MAX(frame.size.width, parentFrame.size.width);
    
    [self setFrame: frame];
}


- (void) dealloc
{    
    [super dealloc];
}


- (void)drawRect:(NSRect)dirtyRect
{
    [super drawRect: dirtyRect];
    
    NSRect      parentFrame = [[self superview] frame];
    NSRect      rc = [self frame];
    
    rc.size.width = MAX(rc.size.width, parentFrame.size.width);
    
    [m_Layout drawInView: self withRect: rc];

    //    NSRect          superViewFrame = [superView frame];
//    CGFloat         horzPos = [[superView horizontalScroller] doubleValue];
//    CGFloat         vertPos = [[superView verticalScroller] doubleValue];
}


- (void) addRepositoryInfo: (CRepositoryInfo*) repInfo
{
    m_RepositoriesInfo.push_back(repInfo);
        
    [m_Layout addItem: [[CRepositoriesListLayoutRow alloc] init: repInfo]];
    [self calcSize];
    [self setNeedsDisplay: YES];
}


- (void)viewDidEndLiveResize
{
//    [self calcSize];
}


- (void)mouseDown:(NSEvent *)theEvent
{
//    NSMutableArray*         pickResult = [[NSMutableArray alloc] initWithCapacity:10];
//    
//    [m_Layout pick: pickResult atPoint: [self convertPoint:[theEvent locationInWindow] fromView:nil]];
//    
//    NSInteger       count = [pickResult count];
//    
//    if (count > 2)
//    {
//        CRepositoriesListLayoutRow*     row = [pickResult objectAtIndex: count-2];
//        
//        if ( [row checked] )
//        {
//            [row setChecked: NO];
//        }
//        else
//        {
//            [row setChecked: YES];
//        }
//        
//        [self setNeedsDisplay: YES];
//    }
}


- (void)refreshForTracesGroup: (CTracesGroupInfo*)pGroupInfo
{
    NSUInteger      count = [m_Layout count];
    NSUInteger      index = 0;
    
    while (index < count)
    {
        CRepositoriesListLayoutRow*         pRow = (CRepositoriesListLayoutRow*) [m_Layout getItem:index];
        CRepositoryInfo*                    pInfo = [pRow repositoryInfo];
        
        if ( pGroupInfo->Group()->HasChannel(pInfo->Channel()) )
        {
            [pRow setChecked: YES];
        }
        else
        {
            [pRow setChecked: NO];
        }
        
        ++ index;
    }
}


@end
