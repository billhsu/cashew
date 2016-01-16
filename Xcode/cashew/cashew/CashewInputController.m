//  Thanks https://github.com/JulianAtGitHub/OpenGL-tutorial-for-Cocoa-master
//

#import "CashewInputController.h"

@interface CashewInputController () {
    NSMutableArray* _objsForKeyEvent;
    NSMutableArray* _keyPressed;
}

@end

@implementation CashewInputController

+ (CashewInputController*)sharedInputController {
    static CashewInputController* instance = nil;

    if (instance == nil) {
        instance = [[CashewInputController alloc] init];
    }

    return instance;
}

- (id)init {
    self = [super init];
    if (self) {
        _objsForKeyEvent = [NSMutableArray array];
        _keyPressed = [NSMutableArray array];
        for (NSUInteger i = 0; i < USHRT_MAX; ++i) {
            [_keyPressed addObject:[NSNumber numberWithBool:NO]];
        }
    }

    return self;
}

- (void)addEventDelegate:(id<CashewInputDelegate>)delegate {
    for (id<CashewInputDelegate> obj in _objsForKeyEvent) {
        if ([obj isEqual:delegate]) {
            NSLog(@"%@ is exist in array objsForKeyEvent", delegate);
            return;
        }
    }
    [_objsForKeyEvent addObject:delegate];
}

- (void)removeEventDelegate:(id<CashewInputDelegate>)delegate {
    for (id<CashewInputDelegate> obj in _objsForKeyEvent) {
        if ([obj isEqual:delegate]) {
            [_objsForKeyEvent removeObject:delegate];
            return;
        }
    }
}

- (void)updateDelegate:(NSTimeInterval)timeInterval {
    for (id<CashewInputDelegate> obj in _objsForKeyEvent) {
        if ([obj respondsToSelector:@selector(updateInput:)]) {
            [obj updateInput:timeInterval];
        }
    }
}

- (void)keysDown:(NSString*)keys {
    for (NSUInteger i = 0; i < [keys length]; ++i) {
        unichar character = [keys characterAtIndex:i];
        [_keyPressed replaceObjectAtIndex:character
                               withObject:[NSNumber numberWithBool:YES]];
        for (id<CashewInputDelegate> obj in _objsForKeyEvent) {
            if ([obj respondsToSelector:@selector(keyDown:)]) {
                [obj keyDown:character];
            }
        }
    }
}

- (void)keysUp:(NSString*)keys {
    for (NSUInteger i = 0; i < [keys length]; ++i) {
        unichar character = [keys characterAtIndex:i];
        [_keyPressed replaceObjectAtIndex:character
                               withObject:[NSNumber numberWithBool:NO]];
        for (id<CashewInputDelegate> obj in _objsForKeyEvent) {
            if ([obj respondsToSelector:@selector(keyUp:)]) {
                [obj keyUp:character];
            }
        }
    }
}

- (BOOL)keyIsPressed:(unichar)key {
    return [[_keyPressed objectAtIndex:key] boolValue];
}

- (void)mouseLeftDown:(NSPoint)locationInWindow {
    for (id<CashewInputDelegate> obj in _objsForKeyEvent) {
        if ([obj respondsToSelector:@selector(mouseLeftDown:)]) {
            [obj mouseLeftDown:locationInWindow];
        }
    }
}

- (void)mouseLeftUp:(NSPoint)locationInWindow {
    for (id<CashewInputDelegate> obj in _objsForKeyEvent) {
        if ([obj respondsToSelector:@selector(mouseLeftUp:)]) {
            [obj mouseLeftUp:locationInWindow];
        }
    }
}

- (void)mouseRightDown:(NSPoint)locationInWindow {
    for (id<CashewInputDelegate> obj in _objsForKeyEvent) {
        if ([obj respondsToSelector:@selector(mouseRightDown:)]) {
            [obj mouseRightDown:locationInWindow];
        }
    }
}

- (void)mouseRightUp:(NSPoint)locationInWindow {
    for (id<CashewInputDelegate> obj in _objsForKeyEvent) {
        if ([obj respondsToSelector:@selector(mouseRightUp:)]) {
            [obj mouseRightUp:locationInWindow];
        }
    }
}

- (void)mouseMoveWithX:(CGFloat)x andY:(CGFloat)y {
    for (id<CashewInputDelegate> obj in _objsForKeyEvent) {
        if ([obj respondsToSelector:@selector(mouseMoveWithX:andY:)]) {
            [obj mouseMoveWithX:x andY:y];
        }
    }
}

- (void)mouseLeftDragWithDX:(CGFloat)dx
                      andDY:(CGFloat)dy
                       andX:(CGFloat)x
                       andY:(CGFloat)y {
    for (id<CashewInputDelegate> obj in _objsForKeyEvent) {
        if ([obj respondsToSelector:@selector(mouseLeftDragWithDX:
                                                            andDY:
                                                             andX:
                                                             andY:)]) {
            [obj mouseLeftDragWithDX:dx andDY:dy andX:x andY:y];
        }
    }
}

- (void)mouseRightDragWithDX:(CGFloat)dx
                       andDY:(CGFloat)dy
                        andX:(CGFloat)x
                        andY:(CGFloat)y {
    for (id<CashewInputDelegate> obj in _objsForKeyEvent) {
        if ([obj respondsToSelector:@selector(mouseRightDragWithDX:
                                                             andDY:
                                                              andX:
                                                              andY:)]) {
            [obj mouseRightDragWithDX:dx andDY:dy andX:x andY:y];
        }
    }
}

- (void)mouseScrollWithX:(CGFloat)x andY:(CGFloat)y {
    for (id<CashewInputDelegate> obj in _objsForKeyEvent) {
        if ([obj respondsToSelector:@selector(mouseScrollWithX:andY:)]) {
            [obj mouseScrollWithX:x andY:y];
        }
    }
}

- (void)mouseEnteredWithX:(CGFloat)x andY:(CGFloat)y {
    for (id<CashewInputDelegate> obj in _objsForKeyEvent) {
        if ([obj respondsToSelector:@selector(mouseEnteredWithX:andY:)]) {
            [obj mouseEnteredWithX:x andY:y];
        }
    }
}

- (void)mouseExitedWithX:(CGFloat)x andY:(CGFloat)y {
    for (id<CashewInputDelegate> obj in _objsForKeyEvent) {
        if ([obj respondsToSelector:@selector(mouseExitedWithX:andY:)]) {
            [obj mouseExitedWithX:x andY:y];
        }
    }
}

@end
