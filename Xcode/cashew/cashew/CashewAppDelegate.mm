//
//  CashewAppDelegate.mm
//  cashew
//
//  Created by Xu, Shipeng on 22/11/14.
//  Copyright (c) 2014 Xu, Shipeng. All rights reserved.
//

#import "CashewAppDelegate.h"
#import "CashewOpenGLView.h"
#import "CashewOpenGLInfoHelper.h"

@interface CashewAppDelegate ()

@property (weak) IBOutlet NSWindow *window;
@property (strong) NSOpenGLView *view;
@end

@implementation CashewAppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    NSOpenGLPixelFormatAttribute attributes[] = {
        NSOpenGLPFAColorSize, 32,
        NSOpenGLPFADepthSize, 16,
        NSOpenGLPFAStencilSize, 8,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
        0
    };
    
    NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
    if (pixelFormat == nil) {
        NSLog(@"Faild create pixel format");
        return;
    }
    
    _view = [[CashewOpenGLView alloc] initWithFrame:self.window.frame pixelFormat:pixelFormat];
    
    [self.window setContentView:_view];
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    [_view clearGLContext];
    [_window setReleasedWhenClosed:NO];
}
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication
{
    return TRUE;
}
- (BOOL)applicationShouldHandleReopen:(NSApplication *)theApplication hasVisibleWindows:(BOOL)flag
{
    if ( flag ) {
        [_window orderFront:self];
    }
    else {
        [_window makeKeyAndOrderFront:self];
    }
    
    return YES;
}

@end
