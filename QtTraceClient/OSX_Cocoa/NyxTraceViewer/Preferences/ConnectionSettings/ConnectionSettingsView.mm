//
//  ConnectionSettingsView.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 1/3/2014.
//  Copyright (c) 2014 Danny Thibaudeau. All rights reserved.
//

#import "ConnectionSettingsView.h"

@implementation CConnectionSettingsView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        
        m_pControls = [[NSMutableArray alloc] init];
        
        [self CreateControls];
    }
    return self;
}


- (void)drawRect:(NSRect)dirtyRect
{
	[super drawRect:dirtyRect];
}


- (BOOL) isFlipped
{
    return YES;
}


- (void) CreateControls
{
    [self CreateControl];
    [self CreateControl];
    [self CreateControl];
    [self CreateControl];
    
    NSControl* control;
    NSUInteger index = 0;
    NSUInteger count = [m_pControls count];
    CGFloat width = 0;
    CGFloat height = 0;
    
    while (index < count)
    {
        control = [m_pControls objectAtIndex:index];
        NSRect frame = [control frame];
        
        height = MAX(height, frame.origin.y + frame.size.height);
        width = MAX(width, frame.origin.x + frame.size.width);

        ++ index;
    }
    
    [self setFrame: NSMakeRect(0, 0, width, height + 10)];
}


- (NSControl*) CreateControl
{
    NSControl*  sibling = NULL;
    NSRect frame = NSMakeRect(10, 10, 600, 100);;
    
    if ( [m_pControls count] > 0 )
    {
        sibling = [m_pControls lastObject];
        frame.origin.y = [sibling frame].origin.y + [sibling frame].size.height + 10;
    }
    
    NSControl* control = [[CConnectionSettingsControl alloc] initWithFrame: frame];
    
    [self addSubview: control];
    [m_pControls addObject:control];
    
    return control;
}

@end
