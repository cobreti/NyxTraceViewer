//
//  RepositoriesListCtrl.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-31.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "RepositoriesListCtrl.h"

@implementation CRepositoriesListCtrl

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("first repository") )];
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("second repository") )];
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("third repository") )];
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("4 repository") )];
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("5 repository") )];
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("6 repository") )];
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("7 repository") )];
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("8 repository") )];
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("9 repository") )];
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("10 repository") )];
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("11 repository") )];
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("12 repository") )];
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("13 repository") )];
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("14 repository") )];
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("15 repository") )];
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("16 repository") )];
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("17 repository") )];
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("18 repository") )];
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("19 repository") )];
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("20 repository") )];
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("21 repository") )];
        [self addRepositoryInfo: new CRepositoryInfo( Nyx::CAString("22 repository") )];
    }
    
    return self;
}

- (BOOL)isFlipped
{
    return YES;
}


- (void)calcSize
{
    CellsList::const_iterator       pos = m_Cells.begin();
    NSSize                          size = NSMakeSize(0, 0);
    NSSize                          cellSize;
    NSRect                          frame = [self frame];
    NSView*                         superView = [self superview];
    NSRect                          superViewFrame = [superView frame];
    
    while (pos != m_Cells.end())
    {
        NSCell* pCell = *pos;
        [pCell calcDrawInfo: frame];

        cellSize = [pCell cellSize];
        size.height += cellSize.height + 10;
        
        if ( cellSize.width > size.width )
            size.width = cellSize.width;
        
        ++ pos;
    }
    
    if ( size.width < superViewFrame.size.width )
        size.width = superViewFrame.size.width;
    
    [self setFrame: NSMakeRect(0, 0, size.width, size.height)];
}


- (void) dealloc
{
    [super dealloc];
}


- (void)drawRect:(NSRect)dirtyRect
{
    NSRect          rc = [self frame];
    CGFloat         y = 0;
        
    CellsList::const_iterator       pos = m_Cells.begin();
    
    while (pos != m_Cells.end())
    {
        NSCell* pCell = *pos;
        NSSize cellSize = [pCell cellSize];
        [pCell drawWithFrame: NSMakeRect(0, y, rc.size.width, cellSize.height) inView:self];
        y += cellSize.height + 10;
        ++pos;
    }
}

- (void) addRepositoryInfo: (CRepositoryInfo*) repInfo
{
    m_RepositoriesInfo.push_back(repInfo);

    NSCell* pCell = [[RepositoryListCtrlCell alloc] initWithRepositoryInfo: repInfo];
    [pCell setFont: [NSFont fontWithName:@"arial" size:12]];
        
    m_Cells.push_back(pCell);
}


- (void)viewDidEndLiveResize
{
    [self calcSize];
}


- (RepositoryListCtrlCell*)cellFromPoint:(NSPoint)pt
{
    CGFloat                     y = 0;
    
    CellsList::const_iterator       pos = m_Cells.begin();
    
    while (pos != m_Cells.end())
    {
        RepositoryListCtrlCell*     pCell = (RepositoryListCtrlCell*)*pos;
        NSSize                      cellSize = [pCell cellSize];
        
        if ( pt.y >= y && pt.y < y + cellSize.height ) {
            return pCell;
        }
        
        y += cellSize.height + 10;
        ++ pos;
    }
    
    return NULL;
}


- (void)mouseDown:(NSEvent *)theEvent
{
    RepositoryListCtrlCell* pCell = [self cellFromPoint: [self convertPoint: [theEvent locationInWindow] fromView:nil] ];
    
    if ( pCell != NULL )
    {
        [pCell toggleSelected];
        [self setNeedsDisplay: YES];
    }
}


@end
