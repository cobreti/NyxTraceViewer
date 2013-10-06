//
//  TracesGroupListenerProtocol.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-10-05.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef NyxTraceViewer_TracesGroupListenerProtocol_h
#define NyxTraceViewer_TracesGroupListenerProtocol_h


@protocol CTracesGroupListenerProtocol

- (void) onTracesViewBeginUpdate;
- (void) onTracesViewEndUpdate;

@end



#endif
