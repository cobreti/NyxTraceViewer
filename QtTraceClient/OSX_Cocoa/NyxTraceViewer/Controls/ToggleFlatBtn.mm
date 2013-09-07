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
}

- (void)setState: (int)state
{
    if ( m_State != state )
    {
        m_State = state;
        [self setNeedsDisplay: YES];
    }
}

- (void)mouseUp:(NSEvent *)theEvent
{
    m_State = 1 - m_State;
    [self setNeedsDisplay: YES];
    
    [self sendAction: m_TargetSelector to:m_Target];
}

- (void)setAction:(SEL)aSelector
{
    m_TargetSelector = aSelector;
}

- (void)setTarget:(id)anObject
{
    m_Target = anObject;
}


@end


