//
//  CTracesGroupCell.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-27.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface CTracesGroupCell : NSCell

- (id)initWithCoder:(NSCoder *)aDecoder;
- (id)initTextCell:(NSString *)aString;
- (id)initImageCell:(NSImage *)image;

@end
