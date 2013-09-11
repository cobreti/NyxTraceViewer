//
//  TracesGroupItem.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-09.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

class CTracesGroupInfo;

@interface CTracesGroupItem : NSControl<NSTextFieldDelegate>
{
    CTracesGroupInfo*       m_pInfo;
    NSCell*                 m_NameCell;
    NSString*               m_Name;
    NSTextField*            m_TextField;
}

- (void)setTracesGroupInfo: (CTracesGroupInfo*)info;
- (void)mouseDown:(NSEvent *)theEvent;
- (void)keyDown:(NSEvent *)theEvent;
- (void)calcSize;

- (void)controlTextDidEndEditing:(NSNotification*)aNotification;

@end
