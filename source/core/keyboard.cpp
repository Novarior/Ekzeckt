#include "keyboard.hpp"
#include <cstdint>

static void HandleInputCallback(void *context, IOReturn result, void *sender,
                                IOHIDValueRef value) {
  keyboardOSX *keyboard = static_cast<keyboardOSX *>(context);
  IOHIDElementRef element = IOHIDValueGetElement(value);
  uint32_t usagePage = IOHIDElementGetUsagePage(element);
  uint32_t usage = IOHIDElementGetUsage(element);

  if (usagePage == kHIDPage_KeyboardOrKeypad) {
    bool pressed = IOHIDValueGetIntegerValue(value) == 1;
    keyboard->keyStates[usage] = pressed;
  }
}

keyboardOSX::keyboardOSX() {
  hidManager = IOHIDManagerCreate(kCFAllocatorDefault, kIOHIDManagerOptionNone);
  IOHIDManagerSetDeviceMatching(hidManager, nullptr);
  IOHIDManagerRegisterInputValueCallback(hidManager, HandleInputCallback, this);
  IOHIDManagerScheduleWithRunLoop(hidManager, CFRunLoopGetCurrent(),
                                  kCFRunLoopDefaultMode);
  IOHIDManagerOpen(hidManager, kIOHIDManagerOptionNone);
}

keyboardOSX::~keyboardOSX() {
  IOHIDManagerClose(hidManager, kIOHIDManagerOptionNone);
  CFRelease(hidManager);
}

bool keyboardOSX::isKeyPressed(uint32_t key) { return keyStates[key]; }

uint32_t keyboardOSX::getPressedKey() {
  for (uint32_t key = 0; key < 256;
       ++key) { // проходим по всем возможным клавишам
    if (keyStates[key]) { // если клавиша нажата
      return key;         // возвращаем её код
    }
  }
  return 0; // возвращаем 0, если ни одна клавиша не нажата
}

// update keyboard
void keyboardOSX::update() {
  CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0, true);
}