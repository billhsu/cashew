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

- (id)initWithFrame:(NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat*)format
{
    self = [super initWithFrame:frameRect pixelFormat:format];
    
    if (self) {
        NSTrackingArea *trackingArea = [[NSTrackingArea alloc] initWithRect:[self bounds]
                                                                    options: (NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved | NSTrackingActiveInKeyWindow )
                                                                      owner:self
                                                                   userInfo:nil];
        [self addTrackingArea:trackingArea];
    }

    return self;
}

//- (void)viewDidMoveToWindow
//{
//    [self addTrackingRect:[self bounds] owner:self userData:nil assumeInside:NO];
//}

- (void)visit:(NSTimer*)theTimer
{
    if ([theTimer isEqual:_timer] == NO) {
        return;
    }
    
    if ([self.delegate respondsToSelector:@selector(update:)]) {
        [[CashewInputController sharedInputController] updateDelegate:[theTimer timeInterval]];
        [self.delegate update:[theTimer timeInterval]];
        [self drawRect:[self bounds]];
    }
}

- (void)drawRect:(NSRect)dirtyRect
{
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
    
    NSRect rect = [self bounds];
    glViewport(0, 0, (GLint) rect.size.width, (GLint) rect.size.height);
}

- (void)reshape
{
    [super reshape];
    
    [[self openGLContext] makeCurrentContext];
    [[self openGLContext] update];
    NSRect rect = [self bounds];
    glViewport(0, 0, rect.size.width, rect.size.height);
    [self.delegate reshapeWidth:rect.size.width height:rect.size.height];
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}

//- (BOOL)becomeFirstResponder
//{
//    return YES;
//}

#pragma mark - keyboard and mouse event

- (void)keyDown:(NSEvent *)theEvent
{
    //[super keyDown:theEvent];
    
    NSString *characters = [theEvent characters];
    [[CashewInputController sharedInputController] keysDown:characters];
    
    NSLog(@"keyDown: %@", characters);
}

- (void)keyUp:(NSEvent *)theEvent
{
    //[super keyUp:theEvent];
    
    NSString *characters = [theEvent characters];
    [[CashewInputController sharedInputController] keysUp:characters];
    
    NSLog(@"keyUp: %@", characters);
}

- (void)mouseDown:(NSEvent *)theEvent
{
    //[super mouseDown:theEvent];
    
    NSPoint location = [theEvent locationInWindow];
    [[CashewInputController sharedInputController] mouseLeftDown:location];
    
    NSLog(@"mouseDown: location:%f %f", location.x, location.y);
}

- (void)mouseUp:(NSEvent *)theEvent
{
    //[super mouseUp:theEvent];
    
    NSPoint location = [theEvent locationInWindow];
    [[CashewInputController sharedInputController] mouseLeftUp:location];
    
    NSLog(@"mouseUp: location:%f %f", location.x, location.y);
}

- (void)rightMouseDown:(NSEvent *)theEvent
{
    //[super rightMouseDown:theEvent];
    
    NSPoint location = [theEvent locationInWindow];
    [[CashewInputController sharedInputController] mouseRightDown:location];
    
    NSLog(@"rightMouseDown: location:%f %f", location.x, location.y);
}

- (void)rightMouseUp:(NSEvent *)theEvent
{
    //[super rightMouseUp:theEvent];
    
    NSPoint location = [theEvent locationInWindow];
    [[CashewInputController sharedInputController] mouseRightUp:location];
    
    NSLog(@"rightMouseUp: location:%f %f", location.x, location.y);
}

- (void)mouseMoved:(NSEvent *)theEvent
{
    //[super mouseMoved:theEvent];
    
    CGFloat x = [theEvent locationInWindow].x;
    CGFloat y = [theEvent locationInWindow].y;
    [[CashewInputController sharedInputController] mouseMoveWithX:x andY:y];
}

- (void)mouseDragged:(NSEvent *)theEvent
{
    //[super mouseDragged:theEvent];
    
    CGFloat x = [theEvent deltaX];
    CGFloat y = [theEvent deltaY];
    [[CashewInputController sharedInputController] mouseLeftDragWithX:x andY:y];
}

- (void)rightMouseDragged:(NSEvent *)theEvent
{
    //[super rightMouseDragged:theEvent];
    
    CGFloat x = [theEvent deltaX];
    CGFloat y = [theEvent deltaY];
    [[CashewInputController sharedInputController] mouseRightDragWithX:x andY:y];
}

- (void)scrollWheel:(NSEvent *)theEvent
{
    //[super scrollWheel:theEvent];
    
    CGFloat x = [theEvent scrollingDeltaX];
    CGFloat y = [theEvent scrollingDeltaY];
    [[CashewInputController sharedInputController] mouseScrollWithX:x andY:y];
}

- (void)mouseEntered:(NSEvent *)theEvent
{
    //[super mouseEntered:theEvent];
    
    NSLog(@"mouseEntered");
}

- (void)mouseExited:(NSEvent *)theEvent
{
    //[super mouseExited:theEvent];
    
    NSLog(@"mouseExited");
}

- (void)cursorUpdate:(NSEvent *)theEvent
{
    //[super cursorUpdate:theEvent];
    
    NSLog(@"cursorUpdate");
}

@end
