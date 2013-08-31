//
//  CTracesGroupCell.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-27.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "TracesGroupCell.h"

@implementation CTracesGroupCell

- (id)initWithCoder:(NSCoder *)aDecoder
{
    return self;
}

- (id)initTextCell:(NSString *)aString
{
    return self;
}

- (id)initImageCell:(NSImage *)image
{
    return self;
}

- (void)drawWithFrame:(NSRect)cellFrame inView:(NSView *)controlView
{
    
//    [[NSColor blueColor] set];
//    NSRect          rc = cellFrame;
//    NSBezierPath*   path = [NSBezierPath bezierPath];
//
//    [path appendBezierPathWithOvalInRect: rc];
//    [path stroke];
}


@end
