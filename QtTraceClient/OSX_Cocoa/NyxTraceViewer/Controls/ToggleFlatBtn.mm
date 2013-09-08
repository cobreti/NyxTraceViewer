//
//  ToggleFlatBtn.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-07.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "ToggleFlatBtn.h"

@implementation CToggleFlatBtn

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        
        int index = 0;
        while (index < kToggleFlatBtn_StatesCount )
        {
            m_Cells[index] = NULL;
            ++ index;
        }
        
        m_State = kToggleFlatBtn_OffState;
    }
    
    return self;
}


- (int)getId
{
    return m_id;
}


- (void)setId:(int)identifier
{
    m_id = identifier;
}


- (BOOL)isFlipped
{
    return YES;
}


- (NSSize) fittingSize
{
    return [self frame].size;
}


- (NSSize) intrinsicContentSize
{
    return [self frame].size;
}


- (void)calcSize
{
    int         index = 0;
    NSSize      size;
    NSSize      cellSize;
    
    while (index < kToggleFlatBtn_StatesCount)
    {
        NSCell* cell = m_Cells[index];
        
        if ( cell != NULL )
        {
            [cell calcDrawInfo:NSZeroRect];
            cellSize = [cell cellSize];
            
            size.width = MAX(size.width, cellSize.width);
            size.height = MAX(size.height, cellSize.height);
        }
        
        ++ index;
    }
    
    [self setFrameSize: size];
    [self setBoundsSize: size];
}

- (void)drawRect:(NSRect)dirtyRect
{
    NSCell*     cell = m_Cells[m_State];
    NSRect      drawFrame;
    
    drawFrame.origin = NSMakePoint(0,0);
    
    if ( cell != NULL )
    {
        drawFrame.size = [cell cellSize];
        [cell drawWithFrame: drawFrame inView:self];
    }
}


- (void)setStateImg: (int)state withResourceImage:(NSString*)ResourceImgName withSize:(NSSize)size
{
    NSString* resourcePath = [[NSBundle mainBundle] pathForResource:ResourceImgName ofType:@"png"];
    NSImage* img = [[NSImage alloc] initWithContentsOfFile:resourcePath];

    if ( size.width != 0 && size.height != 0 )
        [img setSize: size];
    
    if ( m_Cells[state] != NULL )
        [m_Cells[state] release];
    
    m_Cells[state] = [[NSCell alloc] initImageCell: img];
    
    [img release];
}

- (void)setState: (int)state
{
    if ( m_State != state )
    {
        m_State = state;
        [self setNeedsDisplay: YES];
    }
}


- (int)state
{
    return m_State;
}


- (void)mouseUp:(NSEvent *)theEvent
{
    if ( m_State == 1 )
        return;
    
    m_State = 1;
    [self setNeedsDisplay: YES];
    
    if (m_SelectedActionHandler.Valid())
        [self sendAction: m_SelectedActionHandler.Selector() to:m_SelectedActionHandler.Target()];
}

- (void)dealloc
{
    int     index = 0;
    
    while (index < kToggleFlatBtn_StatesCount)
    {
        NSCell* cell = m_Cells[index];
        if (cell)
        {
            [cell release];
        }
        ++ index;
    }
    
    [super dealloc];
}

- (void)setSelectedActionHandler: (const CActionHandlerInfo&)info
{
    m_SelectedActionHandler = info;
}


@end


