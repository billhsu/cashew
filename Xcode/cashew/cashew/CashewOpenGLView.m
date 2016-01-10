//  Shipeng Xu
//  CashewOpenGLView.m
//
//  Originally Created by wei.zhu on 1/23/13.
//  Copyright (c) 2013 Juicer. All rights reserved.
//

#import "CashewOpenGLView.h"
#import "CashewInputController.h"
#import <OpenGL/gl3.h>

@implementation CashewOpenGLView

- (void)updateTrackingAreas {
    if (self) {
        [self removeTrackingArea:trackingArea];
        trackingArea = [[NSTrackingArea alloc]
            initWithRect:[self bounds]
                 options:(NSTrackingMouseEnteredAndExited |
                          NSTrackingMouseMoved | NSTrackingActiveInKeyWindow)
                   owner:self
                userInfo:nil];
        [self addTrackingArea:trackingArea];
    }
}

- (id)initWithFrame:(NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat*)format {
    self = [super initWithFrame:frameRect pixelFormat:format];
    [self setWantsBestResolutionOpenGLSurface:YES];
    if (self) {
        trackingArea = [[NSTrackingArea alloc]
            initWithRect:[self bounds]
                 options:(NSTrackingMouseEnteredAndExited |
                          NSTrackingMouseMoved | NSTrackingActiveInKeyWindow)
                   owner:self
                userInfo:nil];
        [self addTrackingArea:trackingArea];
    }

    return self;
}

//- (void)viewDidMoveToWindow
//{
//    [self addTrackingRect:[self bounds] owner:self userData:nil
//    assumeInside:NO];
//}

- (void)visit:(NSTimer*)theTimer {
    if ([theTimer isEqual:_timer] == NO) {
        return;
    }

    if ([self.delegate respondsToSelector:@selector(update:)]) {
        [[CashewInputController sharedInputController]
            updateDelegate:[theTimer timeInterval]];
        [self.delegate update:[theTimer timeInterval]];
        [self drawRect:[self bounds]];
    }
}

- (void)drawRect:(NSRect)dirtyRect {
    // Drawing code here.
    [[self openGLContext] makeCurrentContext];

    if ([self.delegate respondsToSelector:@selector(render)]) {
        [self.delegate render];
    }

    [[self openGLContext] flushBuffer];
}

- (void)update  // moved or resized
{
    [super update];

    [[self openGLContext] makeCurrentContext];
    [[self openGLContext] update];

    //    NSRect rect = [self bounds];
    //    glViewport(0, 0, (GLint)rect.size.width, (GLint)rect.size.height);
}

- (void)reshape {
    [super reshape];

    [[self openGLContext] makeCurrentContext];
    [[self openGLContext] update];
    NSRect rect = [self bounds];
    NSRect rrect = [self convertRectToBacking:rect];

    //    glViewport(0, 0, rect.size.width, rect.size.height);
    [self.delegate reshapeRect:rect backing:rrect];
}

- (BOOL)acceptsFirstResponder {
    return YES;
}

//- (BOOL)becomeFirstResponder
//{
//    return YES;
//}

#pragma mark - keyboard and mouse event

- (void)keyDown:(NSEvent*)theEvent {
    //[super keyDown:theEvent];

    NSString* characters = [theEvent characters];
    [[CashewInputController sharedInputController] keysDown:characters];
}

- (void)keyUp:(NSEvent*)theEvent {
    //[super keyUp:theEvent];

    NSString* characters = [theEvent characters];
    [[CashewInputController sharedInputController] keysUp:characters];
}

- (void)mouseDown:(NSEvent*)theEvent {
    //[super mouseDown:theEvent];
    NSPoint windowPos =
        [self convertPointToBacking:[theEvent locationInWindow]];
    [[CashewInputController sharedInputController] mouseLeftDown:windowPos];
}

- (void)mouseUp:(NSEvent*)theEvent {
    //[super mouseUp:theEvent];

    NSPoint windowPos =
        [self convertPointToBacking:[theEvent locationInWindow]];
    [[CashewInputController sharedInputController] mouseLeftUp:windowPos];
}

- (void)rightMouseDown:(NSEvent*)theEvent {
    //[super rightMouseDown:theEvent];

    NSPoint location = [theEvent locationInWindow];
    [[CashewInputController sharedInputController] mouseRightDown:location];
}

- (void)rightMouseUp:(NSEvent*)theEvent {
    //[super rightMouseUp:theEvent];

    NSPoint windowPos =
        [self convertPointToBacking:[theEvent locationInWindow]];
    [[CashewInputController sharedInputController] mouseRightUp:windowPos];
}

- (void)mouseMoved:(NSEvent*)theEvent {
    //[super mouseMoved:theEvent];
    NSPoint windowPos =
        [self convertPointToBacking:[theEvent locationInWindow]];
    CGFloat x = windowPos.x;
    CGFloat y = windowPos.y;
    [[CashewInputController sharedInputController] mouseMoveWithX:x andY:y];
}

- (void)mouseDragged:(NSEvent*)theEvent {
    //[super mouseDragged:theEvent];
    NSPoint windowPos =
        [self convertPointToBacking:[theEvent locationInWindow]];
    NSPoint deltaPos = NSMakePoint([theEvent deltaX], [theEvent deltaY]);
    deltaPos = [self convertPointToBacking:deltaPos];
    CGFloat dx = deltaPos.x;
    CGFloat dy = deltaPos.y;
    CGFloat x = windowPos.x;
    CGFloat y = windowPos.y;

    [[CashewInputController sharedInputController] mouseLeftDragWithDX:dx
                                                                 andDY:dy
                                                                  andX:x
                                                                  andY:y];
}

- (void)rightMouseDragged:(NSEvent*)theEvent {
    //[super rightMouseDragged:theEvent];
    NSPoint windowPos =
        [self convertPointToBacking:[theEvent locationInWindow]];
    CGFloat dx = [theEvent deltaX];
    CGFloat dy = [theEvent deltaY];
    CGFloat x = windowPos.x;
    CGFloat y = windowPos.y;
    [[CashewInputController sharedInputController] mouseRightDragWithDX:dx
                                                                  andDY:dy
                                                                   andX:x
                                                                   andY:y];
}

- (void)scrollWheel:(NSEvent*)theEvent {
    //[super scrollWheel:theEvent];

    CGFloat x = [theEvent scrollingDeltaX];
    CGFloat y = [theEvent scrollingDeltaY];
    [[CashewInputController sharedInputController] mouseScrollWithX:x andY:y];
}

- (void)mouseEntered:(NSEvent*)theEvent {
    //[super mouseEntered:theEvent];
    NSPoint windowPos =
        [self convertPointToBacking:[theEvent locationInWindow]];
    CGFloat x = windowPos.x;
    CGFloat y = windowPos.y;
    [[CashewInputController sharedInputController] mouseEnteredWithX:x andY:y];
    NSLog(@"mouseEntered");
}

- (void)mouseExited:(NSEvent*)theEvent {
    //[super mouseExited:theEvent];
    NSPoint windowPos =
        [self convertPointToBacking:[theEvent locationInWindow]];
    CGFloat x = windowPos.x;
    CGFloat y = windowPos.y;
    [[CashewInputController sharedInputController] mouseExitedWithX:x andY:y];
    NSLog(@"mouseExited");
}

- (void)cursorUpdate:(NSEvent*)theEvent {
    //[super cursorUpdate:theEvent];
    NSLog(@"cursorUpdate");
    NSPoint windowPos =
        [self convertPointToBacking:[theEvent locationInWindow]];
    CGFloat x = windowPos.x;
    CGFloat y = windowPos.y;
    [[CashewInputController sharedInputController] mouseMoveWithX:x andY:y];
}

@end
