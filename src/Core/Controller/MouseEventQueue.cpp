/*
 Shipeng Xu
 billhsu.x@gmail.com
 */

#include "MouseEventQueue.h"
namespace MouseEventQueue {
    std::queue<MouseEvent> queue;

    void init() {
        queue = std::queue<MouseEvent>();
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
}