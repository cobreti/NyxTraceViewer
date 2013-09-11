//
//  CellsLayout.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-10.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Foundation/Foundation.h>


typedef struct _SCellsLayoutMargins
{
    CGFloat     top;
    CGFloat     left;
    CGFloat     bottom;
    CGFloat     right;

} SCellsLayoutMargins;


inline SCellsLayoutMargins  MakeLayoutMargins(CGFloat left, CGFloat top, CGFloat right, CGFloat bottom)
{
    SCellsLayoutMargins margins = {top, left, bottom, right};
    
    return margins;
}


@interface CCellsLayout : NSObject
{
    NSRect                          m_Rect;
    SCellsLayoutMargins             m_Margins;
}

- (id)init;
- (void)addItem: (CCellsLayout*)item;
- (void)update: (NSPoint)pt;
- (void)drawInView: (NSView*)view withRect: (NSRect)frame;
- (NSRect)layoutRect;
- (void)setMargins: (SCellsLayoutMargins)margins;
- (SCellsLayoutMargins)margins;
- (void)pick: (NSMutableArray*)items atPoint: (NSPoint)pt;

@end
