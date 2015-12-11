/*
 Shipeng Xu
 billhsu.x@gmail.com
 */
#ifndef __cashew__MouseEventQueue__
#define __cashew__MouseEventQueue__
#include "Mouse.h"
#include "MouseEvent.h"
#include <queue>
namespace MouseEventQueue {
    void init();
    bool pollEvent(MouseEvent& event);
    void addEvent(const MouseEvent event);
    void clear();
    // copy the queue
    std::queue<MouseEvent> getQueueCpy();
}
#endif /* defined(__cashew__MouseEventQueue__) */
