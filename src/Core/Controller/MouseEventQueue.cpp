/*
 Shipeng Xu
 billhsu.x@gmail.com
 */

#include "MouseEventQueue.h"
namespace MouseEventQueue {
    std::queue<MouseEvent> queue;

    void init() {
        clear();
    }
    bool pollEvent(MouseEvent& event) {
        if (queue.size() == 0) {
            return false;
        }
        event = queue.front();
        queue.pop();
        return true;
    }
    void addEvent(const MouseEvent event) {
        queue.push(event);
    }
    void clear() {
        queue = std::queue<MouseEvent>();
    }
}