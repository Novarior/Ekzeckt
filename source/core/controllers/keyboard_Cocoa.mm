#import <Cocoa/Cocoa.h>
#include <set>

namespace keyboardCocoa {

static std::set<uint16_t> pressedKeys;
static std::set<uint16_t> releasedKeys;
static id keyEventMonitor = nil;

static void handleKeyboardEvent(NSEvent *event) {
    if (event.type == NSEventTypeKeyDown) {
        pressedKeys.insert(event.keyCode);
        releasedKeys.erase(event.keyCode);
    } else if (event.type == NSEventTypeKeyUp) {
        pressedKeys.erase(event.keyCode);
        releasedKeys.insert(event.keyCode);
    }
}

void setupCocoaKeyboard(void *windowHandle) {
    if (keyEventMonitor != nil)
        return;

    keyEventMonitor = [NSEvent addLocalMonitorForEventsMatchingMask:(NSEventMaskKeyDown | NSEventMaskKeyUp)
                                                              handler:^NSEvent *(NSEvent *event) {
        handleKeyboardEvent(event);
        return event;
    }];
}

bool keyIsPressed(uint16_t keyCode) {
    return pressedKeys.count(keyCode) > 0;
}

bool keyIsReleased(uint16_t keyCode) {
    auto it = releasedKeys.find(keyCode);
    if (it != releasedKeys.end()) {
        releasedKeys.erase(it);
        return true;
    }
    return false;
}

void clearKeyStates() {
    pressedKeys.clear();
    releasedKeys.clear();
}

}  // namespace keyboardCocoa
