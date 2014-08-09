//
//  ConnectionSettingsControl.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 1/3/2014.
//  Copyright (c) 2014 Danny Thibaudeau. All rights reserved.
//

#import "ConnectionSettingsControl.h"

@implementation CConnectionSettingsControl

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
	[super drawRect:dirtyRect];

	[[NSColor blueColor] set];
    
    NSBezierPath*       path = [NSBezierPath bezierPathWithRect:[self bounds]];
    
    [path stroke];
    
    // Drawing code here.
}

- (BOOL)isFlipped
{
    return YES;
}

@end
