//
//  RepositoriesListCtrl.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-31.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "RepositoriesListCtrl.h"
#import "RepositoryListItem.h"

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
    NSRect                                  itemFrame;
    CGFloat                                 y = 0;
    RepositoryListItems::const_iterator     pos = m_Items.begin();
    NSSize                                  size = NSMakeSize(0, 0);
    NSView*                                 superView = [self superview];
    NSRect                                  superViewFrame = [superView frame];
    
    while (pos != m_Items.end())
    {
        CRepositoryListItem*    item = *pos;
        [item calcSize];
        itemFrame = [item frame];
        
        [item setFrame: NSMakeRect(0, y, itemFrame.size.width, itemFrame.size.height)];
        y += itemFrame.size.height;
        
        size.height += itemFrame.size.height;

        if ( itemFrame.size.width > size.width )
            size.width = itemFrame.size.width;

        ++ pos;
    }
    
    if ( size.width < superViewFrame.size.width )
        size.width = superViewFrame.size.width;

    [self setFrame: NSMakeRect(0, 0, size.width, size.height)];
}


- (void) dealloc
{
    while (!m_Items.empty())
    {
        [m_Items.front() release];
        m_Items.pop_front();
    }
    
    [super dealloc];
}


- (void)drawRect:(NSRect)dirtyRect
{
    [super drawRect: dirtyRect];
    
//    NSRect          superViewFrame = [superView frame];
//    CGFloat         horzPos = [[superView horizontalScroller] doubleValue];
//    CGFloat         vertPos = [[superView verticalScroller] doubleValue];
}

- (void) addRepositoryInfo: (CRepositoryInfo*) repInfo
{
    m_RepositoriesInfo.push_back(repInfo);
    
    NSRect                  itemFrame = [self bounds];
    itemFrame.origin.y = 0;
    itemFrame.size.height = 20;
    CRepositoryListItem*    item = [[CRepositoryListItem alloc] initWithFrame: itemFrame];
    [item setRepositoryInfo: repInfo];
    [item setFont: [NSFont fontWithName:@"arial" size:12]];
    
    [self addSubview: item];
    m_Items.push_back(item);
}


- (void)viewDidEndLiveResize
{
//    [self calcSize];
}


@end
