#ifndef KEYBOARD
#define KEYBOARD

#include <IOKit/hid/IOHIDLib.h>
#include <cstdint>
#include <map>

class keyboardOSX {
public:
  std::map<uint32_t, bool> keyStates;
  IOHIDManagerRef hidManager;

  keyboardOSX();
  ~keyboardOSX();

  bool isKeyPressed(uint32_t key);
  uint32_t getPressedKey();
  void update();
};

#endif /* KEYBOARD */