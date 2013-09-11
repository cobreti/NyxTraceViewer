//
//  CellsLayout.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-10.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CCellsLayout : NSObject
{
    NSRect              m_Rect;
}

- (id)init;
- (void)addItem: (CCellsLayout*)item;
- (void)update: (NSPoint)pt;
- (void)drawInView: (NSView*)view;
- (NSRect)layoutRect;

@end
