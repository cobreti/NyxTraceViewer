//
//  CTracesGroupView.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-25.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "SourcesView.h"
#import "../../Controls/RepositoriesList/RepositoriesListCtrl.h"

#include <Nyx.hpp>
#include "TraceClientCoreModule.hpp"


@implementation CSourcesView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {

        [self setHasHorizontalScroller: YES];
        [self setHasVerticalScroller: YES];
        
        mCtrl = [[CRepositoriesListCtrl alloc] initWithFrame: [self frame]];
//        [mCtrl setAutoresizingMask: NSViewHeightSizable | NSViewWidthSizable];
        [self setDocumentView: mCtrl];
        [mCtrl calcSize];
        
    }
    
    return self;
}

-(BOOL)isFlipped
{
    return YES;
}


- (void)dealloc
{    
    [mCtrl release];
    
    NYXTRACE(0x0, L"TracesGroupView dealloc");
    [super dealloc];
}

- (void)drawRect:(NSRect)dirtyRect
{
    [super drawRect: dirtyRect];
}

- (void)awakeFromNib
{   
    [self setHasHorizontalScroller: YES];
    [self setHasVerticalScroller: YES];
    
    mCtrl = [[CRepositoriesListCtrl alloc] initWithFrame: [self frame]];
    [mCtrl setAutoresizingMask: NSViewHeightSizable | NSViewWidthSizable];
    [self setDocumentView: mCtrl];
    [mCtrl calcSize];    
}

- (void)onNewChannel: (NSDictionary*)params
{
    TraceClientCore::CTraceChannel* pChannel = (TraceClientCore::CTraceChannel*)[[params objectForKey:@"channel"] pointerValue];
    
    NYXTRACE(0x0, L"RepositoriesListCtrl - onNewChannel");
    
    CRepositoryInfo*    pRepInfo = new CRepositoryInfo( pChannel->Name() );
    pRepInfo->Channel() = pChannel;
    
    [mCtrl addRepositoryInfo: pRepInfo];
}


- (void)refreshForGroup: (CTracesGroupInfo*)pGroupInfo
{
    [mCtrl refreshForTracesGroup:pGroupInfo];
}


@end

